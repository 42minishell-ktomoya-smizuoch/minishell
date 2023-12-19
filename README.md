# Minishell

## 概要
Minishellは、42のプロジェクトの一環として開発された、シンプルで使いやすいコマンドラインシェルです。基本的なシェル機能をC言語で実装し、UNIXの哲学に基づいた設計を目指しています❗️

## 特徴
- 独自のコマンド解析機能
- カスタマイズ可能なプロンプト
- C言語のみでの実装による高い移植性

## 動作環境
- UNIX系OS（Linux, macOS等）
- Cコンパイラ（gcc, clang等）

## インストール方法
```bash
git clone [リポジトリURL]
cd minishell
make
```

## 使い方
```bash
./minishell
minishell$ [コマンド入力]
```
![minishell_use](https://github.com/42minishell-ktomoya-smizuoch/minishell/assets/124504326/96dfa1e4-17d3-4ee8-8a25-33126e34e699)

## 機能一覧
- 基本的なシェルコマンドの実行
- 環境変数の管理
- シグナル処理
- パイプラインとリダイレクトのサポート
