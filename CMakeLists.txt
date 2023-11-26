# CLionでDXLibraryの開発をするに当たって環境構築の参考にさせていただいたサイト
# Title: DXライブラリをCMakeと併用する方法
# URL:   https://qiita.com/ishioka0222/items/db2166e63b779328a779

# CMake バージョン指定
cmake_minimum_required(VERSION 3.26)

# プロジェクト名
project(GA_K04_CPP_Clion)

# 使用する言語のバージョン指定
set(CMAKE_CXX_STANDARD 23)

# DXLIB_DIRの定義
set(DXLIB_DIR ${CMAKE_SOURCE_DIR}/dxLib)

# 自動インストール
include(ExternalProject)
ExternalProject_Add(DxLibDownload
        URL https://dxlib.xsrv.jp/DxLib/DxLibNoneModel_NoneSoftDrawCode_VC_3_23.zip
        SOURCE_DIR ${DXLIB_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
)

# `src`ディレクトリをCMakeのビルド対象に追加します
add_subdirectory("./src")