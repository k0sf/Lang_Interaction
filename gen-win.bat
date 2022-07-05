@echo off


go build -buildmode=c-shared -o build/windows/libdemo.dll go-apps/demo.go