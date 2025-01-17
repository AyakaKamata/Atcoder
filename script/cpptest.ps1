$problem_name = $Args[0]
$base_url = ($problem_name.Replace("_", "-")).Substring(0, ($problem_name.Length) - 2)
$test_dir = "test/$problem_name"

# 問題のURLを生成
$url = "https://atcoder.jp/contests/$base_url/tasks/$problem_name"

# テストケースのディレクトリが存在しなければ作成し、テストケースをダウンロード
if (! (Test-Path $test_dir)) {
  oj dl -d $test_dir $url  # "oj dl" コマンドでテストケースをダウンロード
}


# コンパイルとテスト実行
g++ src/$problem_name.cpp -o bin/$problem_name.out && oj test -c bin/$problem_name.out -d $test_dir && oj s $url src/$problem_name.cpp && Remove-Item -Force -Path $test_dir -ErrorAction SilentlyContinue
Remove-Item -Force -Path bin/* -ErrorAction SilentlyContinue
