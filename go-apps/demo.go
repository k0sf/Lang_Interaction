package main

import "C"

func main() {

}

//export Hello
func Hello() string {
	return "Hello"
}

//export AddInt
func AddInt(a, b int) int {
	return a + b
}

//export ToCString
func ToCString(str string) *C.char {
	cs := C.CString(str)
	return cs
}
