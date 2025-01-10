. ".venv/Scripts/Activate.ps1"

$problem_name = $Args[0]
$base_url = ($problem_name.Replace("_", "-")).Substring(0, ($problem_name.Length) - 2)
$test_dir = "test/$problem_name"

# 問題のURLを生成
$url = "https://atcoder.jp/contests/$base_url/tasks/$problem_name"

# テストケースのディレクトリが存在しなければ作成し、テストケースをダウンロード
if (! (Test-Path $test_dir)) {
  oj dl -d $test_dir $url  # "oj dl" コマンドでテストケースをダウンロード
}

# テストの実行
oj t -c "python src/$problem_name.py" -d $test_dir/ --no-print-input && oj s $url src/$problem_name.py --language 5078 && Remove-Item -Recurse -Force $test_dir