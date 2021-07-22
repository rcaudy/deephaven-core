#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <boost/utility/string_view.hpp>

namespace deephaven {
namespace openAPI {
namespace utility {
struct Void {};

template<typename Dest, typename Src>
inline Dest bit_cast(const Src &item) {
  static_assert(sizeof(Src) == sizeof(Dest), "Src and Dest are not the same size");
  Dest dest;
  memcpy(static_cast<void*>(&dest), static_cast<const void*>(&item), sizeof(Dest));
  return dest;
}

// A more efficient ostringstream that also allows you to grab the internal buffer if you want it.
// Or, if you don't want to use the internal buffer, it allows you to provide your own.
class MyOstringStream final : private std::basic_streambuf<char>, public std::ostream {
  using Buf = std::basic_streambuf<char>;
public:
  MyOstringStream();
  explicit MyOstringStream(std::string *clientBuffer);
  MyOstringStream(const MyOstringStream &other) = delete;
  MyOstringStream &operator=(const MyOstringStream &other) = delete;
  ~MyOstringStream() final;

  std::string &str() { return *dest_; }

private:
  Buf::int_type overflow(int c) final;
  std::streamsize xsputn(const char *s, std::streamsize n) final;

  std::string internalBuffer_;
  std::string *dest_;
};

namespace internal {
// Dumps chars up to the next %o or NUL. Updates *fmt to the point past the %o or at the NUL.
// Returns true iff %o was the last thing seen.
bool dumpFormat(std::ostream &s, const char **fmt, bool placeholderExpected);
}  // namespace internal

std::ostream &streamf(std::ostream &s, const char *fmt);

template<typename HEAD, typename... REST>
std::ostream &streamf(std::ostream &s, const char *fmt, const HEAD &head, REST &&... rest) {
  (void) deephaven::openAPI::utility::internal::dumpFormat(s, &fmt, true);
  s << head;
  return streamf(s, fmt, std::forward<REST>(rest)...);
}

template<typename... ARGS>
std::ostream &coutf(const char *fmt, ARGS &&... args) {
  streamf(std::cout, fmt, std::forward<ARGS>(args)...);
#ifndef NDEBUG
  std::cout.flush();
#endif
  return std::cout;
}

template<typename... ARGS>
std::ostream &cerrf(const char *fmt, ARGS &&... args) {
  streamf(std::cerr, fmt, std::forward<ARGS>(args)...);
#ifndef NDEBUG
  std::cerr.flush();
#endif
  return std::cerr;
}

template<typename... ARGS>
void appendf(std::string *buffer, const char *fmt, ARGS &&... args) {
  MyOstringStream s(buffer);
  streamf(s, fmt, std::forward<ARGS>(args)...);
}

template<typename... ARGS>
std::string stringf(const char *fmt, ARGS &&... args) {
  std::string result;
  appendf(&result, fmt, std::forward<ARGS>(args)...);
  return result;
}

namespace internal {
// Forward declaration for class
template<typename Iterator>
class SeparatedListAdaptor;

// Then, forward declaration for operator<<
template<typename Iterator>
std::ostream &operator<<(std::ostream &s, const SeparatedListAdaptor<Iterator> &o);

// Finally, the class
template<typename Iterator>
class SeparatedListAdaptor {
public:
  SeparatedListAdaptor(Iterator begin, Iterator end, const char *separator) :
      begin_(begin), end_(end), separator_(separator) {}

protected:
  virtual void dumpElement(std::ostream &s, const decltype(*std::declval<Iterator>()) &item) const {
    s << item;
  }

private:
  Iterator begin_;
  Iterator end_;
  const char *separator_;

  friend std::ostream &operator<<<>(std::ostream &s, const SeparatedListAdaptor &o);
};

template<typename Iterator, typename Callback>
class SeparatedListAdaptorWithCallback : public SeparatedListAdaptor<Iterator> {
public:
  SeparatedListAdaptorWithCallback(Iterator begin, Iterator end, const char *separator, Callback cb) :
      SeparatedListAdaptor<Iterator>(begin, end, separator), cb_(std::move(cb)) {}

protected:
  virtual void dumpElement(std::ostream &s, const decltype(*std::declval<Iterator>()) &item) const {
    cb_(s, item);
  }

private:
  Callback cb_;
};

template<typename Iterator>
std::ostream &operator<<(std::ostream &s, const SeparatedListAdaptor<Iterator> &o) {
  for (auto current = o.begin_; current != o.end_; ++current) {
    if (current != o.begin_) {
      s << o.separator_;
    }
    o.dumpElement(s, *current);
  }
  return s;
}
}  // namespace internal

template<typename Iterator>
internal::SeparatedListAdaptor<Iterator> separatedList(Iterator begin, Iterator end,
    const char *separator = ", ") {
  return internal::SeparatedListAdaptor<Iterator>(begin, end, separator);
}

template<typename Iterator, typename Callback>
internal::SeparatedListAdaptorWithCallback<Iterator, Callback> separatedList(Iterator begin, Iterator end,
    const char *separator, Callback cb) {
  return internal::SeparatedListAdaptorWithCallback<Iterator, Callback>(begin, end, separator, std::move(cb));
}
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
