﻿//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
using Deephaven.Dh_NetClient;
using Xunit.Abstractions;

namespace Deephaven.Dh_NetClientTests;

public class ValidationTest(ITestOutputHelper output) {
  [Fact]
  public void Select() {
    string[][] badSelects = [
      [ "X = 3)" ],
      ["S = `hello`", "T = java.util.regex.Pattern.quote(S)"], // Pattern.quote not on whitelist
      ["X = Math.min(3, 4)"] // Math.min not on whitelist
    ];
    string[][] goodSelects = [
      ["X = 3"],
      ["S = `hello`", "T = S.length()"], // instance methods of String ok
      ["X = min(3, 4)"], // "builtin" from GroovyStaticImports
      ["X = isFinite(3)"], // another builtin from GroovyStaticImports
    ];

    using var ctx = CommonContextForTests.Create(new ClientOptions());
    var thm = ctx.Client.Manager;
    using var staticTable = thm.EmptyTable(10)
      .Update("X = 12", "S = `hello`");
    TestSelectsHelper("static Table", staticTable, badSelects, goodSelects);
  }

  [Fact]
  public void Where() {
    string[] badWheres = [
      "X > 3)", // syntax error
      "S = new String(`hello`)", // new not allowed
      "S = java.util.regex.Pattern.quote(S)", // Pattern.quote not on whitelist
      "X = Math.min(3, 4)" // Math.min not on whitelist
    ];

    string[] goodWheres = [
      "X = 3",
      "S = `hello`",
      "S.length() = 17", // instance methods of String ok
      "X = min(3, 4)", // "builtin" from GroovyStaticImports
      "X = isFinite(3)", // another builtin from GroovyStaticImports
      "X in 3, 4, 5"
    ];

    using var ctx = CommonContextForTests.Create(new ClientOptions());
    var thm = ctx.Client.Manager;
    using var staticTable = thm.EmptyTable(10)
      .Update("X = 12", "S = `hello`");
    TestWheresHelper("static Table", staticTable, badWheres, goodWheres);
  }

  private void TestWheresHelper(string what, TableHandle table,
    IEnumerable<string> badWheres, IEnumerable<string> goodWheres) {
    foreach (var bw in badWheres) {
      try {
        output.WriteLine($"Trying {what} {bw}");
        using var dummy = table.Where(bw);
      } catch (Exception e) {
        output.WriteLine($"{what}: {bw}: Failed *as expected* with: {e.Message}");
        continue;
      }

      throw new Exception($"{what}: {bw}: Expected to fail, but succeeded");
    }

    foreach (var gw in goodWheres) {
      using var dummy = table.Where(gw);
      output.WriteLine($"{what}: {gw}: Succeeded as expected");
    }
  }

  private void TestSelectsHelper(string what, TableHandle table,
    IEnumerable<string[]> badSelects, IEnumerable<string[]> goodSelects) {
    foreach (var bs in badSelects) {
      var printable = string.Join(", ", bs);
      try {
        using var dummy = table.Select(bs);
      } catch (Exception e) {
        output.WriteLine($"{what}: {printable}: Failed as expected with: {e.Message}");
        continue;
      }

      throw new Exception($"{what}: {printable}: Expected to fail, but succeeded");
    }

    foreach (var gs in goodSelects) {
      var printable = string.Join(", ", gs);
      using var dummy = table.Select(gs);
      output.WriteLine($"{what}: {printable}: Succeeded as expected");
    }
  }
}
