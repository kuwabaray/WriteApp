# WriteApp
WriteAppは、ウィンドウに描画した文字を認識して標準出力するMAC用アプリケーションです。

動作はリンク先の動画のようになります。
https://youtu.be/OL59D4prw3Q



# 実装している機能

・マウスでウィンドウへの描画(Cocoa, OpenGL)

・Enterーキーで描画されているもののクリア(OpenGL)

・Spaceキーで、ウィンドウに描画されている英数字の標準出力(Google Cloud Vision API)

# 使用した技術
言語... Objective-C++, C++, Python

主なフレームワーク... Cocoa, OpenGL, Python3.8

文字の描画はマウスのドラッグしている座標に画像(WriteApp/Image/Droplet.png)を描画しています。

Enterキーを押すと、ウィンドウをスクリーンショットのように画像データにして、Google Cloud Vision API に送信します。

C++にPythonを組み込み(WriteApp/Script/Connect_Python.hpp), 
Google Cloud Vision API を叩くPythonファイル(WriteApp/Script/gcvision_api.py)を呼び出しています。

# 注意事項
WriteApp/Script/gcvision_api.py のAPI_KEYを独自のGoogle Cloud Vision APIのキーに書き換えないと動作しません。
