$problem_name = $Args[0]
$test_dir = "test/$problem_name"

if ($problem_name.Length -ge 5 -and ($problem_name.Substring(0, 5) -eq "ALDS1" -or $problem_name.Substring(0, 3) -eq "DPL"-or $problem_name.Substring(0, 3) -eq "GRL"-or $problem_name.Substring(0, 3) -eq "NTL") -or $problem_name -match '^\d') {
  $url = "https://onlinejudge.u-aizu.ac.jp/problems/$problem_name"
} else {
  $base_url = if ($problem_name.Length -ge 2) { $problem_name.Replace("_", "-").Substring(0, $problem_name.Length - 2) } else { $problem_name.Replace("_", "-") }

  # 問題のURLを生成
  $url = "https://atcoder.jp/contests/$base_url/tasks/$problem_name"
}

# テストケースのディレクトリが存在しなければ作成し、テストケースをダウンロード
if (! (Test-Path $test_dir)) {
  oj dl -d $test_dir $url  # "oj dl" コマンドでテストケースをダウンロード
}

# コンパイルとテスト実行
if ($problem_name.Length -ge 5 -and ($problem_name.Substring(0, 5) -eq "ALDS1" -or $problem_name.Substring(0, 3) -eq "DPL" -or $problem_name.Substring(0, 3) -eq "GRL"-or $problem_name.Substring(0, 3) -eq "NTL") -or $problem_name -match '^\d') {
  g++ src/$problem_name.cpp -o bin/$problem_name.out && oj test -c bin/$problem_name.out -d $test_dir && Remove-Item -Force -Path $test_dir -ErrorAction SilentlyContinue
} else {
  g++ src/$problem_name.cpp -o bin/$problem_name.out && oj test -c bin/$problem_name.out -d $test_dir && oj s $url src/$problem_name.cpp && Remove-Item -Force -Path $test_dir -ErrorAction SilentlyContinue
}
Remove-Item -Force -Path bin/* -ErrorAction SilentlyContinue