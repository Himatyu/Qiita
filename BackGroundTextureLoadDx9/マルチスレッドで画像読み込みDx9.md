# DirectX9とC++11のマルチスレッドを使用して裏画面ロードを実装する話

## 今回の目的
マルチスレッドの素晴らしさを知ってほしい

##今回作るもの
裏で画像を読み込みながら動くローディング画面を出す

## なぜDirectX"9"なのか。
私が聞きたいですね、HALの広報にでも聞いて下さい。
「お宅はいつまでDirectX9縛りの課題を出すのか」と

## 環境
IDEのバージョンとDirectXのバージョン、CPU

## 準備
Threadが使用できるのか確認する

## 実装
* NowLodiongテクスチャロード・描画
* Thread軌道
* 裏で画像ロード
* 完了通知
* nowLoad終了、画像描画
* 後始末

##注意点
WRアクセス
DirectX9のデバイス：https://msdn.microsoft.com/ja-jp/library/ee422106(v=vs.85).aspx


##ゲームに組み込むには






![aaa](tex1.jpg "")
