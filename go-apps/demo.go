package main

/*
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char* name;
    char* desc;
}ctx_info;
//ctx_info *createCtx(char* name,char* desc) {
//    ctx_info *obj = (ctx_info *)malloc(sizeof(ctx_info));
//    obj->name = name;
//    obj->desc = desc;
//    return obj;
//}

typedef struct {
    char* name;
    int num;
} langs;


*/
import "C"
import (
    "errors"
    "fmt"
    "reflect"
    "unsafe"
)


func main() {
    var x Langs
    a := GetLangs()
    x.RP(a)
    fmt.Println(x)
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

//export SetMyPoint
func SetMyPoint(p uintptr) { //修改传入的结构体
    mp := (*MyPoint)(unsafe.Pointer(p)) //将指针p强制转换为MyPoint类型
    mp.Name = "名称:" + mp.Name
    mp.X = 1 + mp.X
    mp.Y = 2 + mp.Y
    fmt.Println(mp)
}

//export GetMyInfo
func GetMyInfo(str *C.char) C.ctx_info {
    info := MyInfo{
        Name:"名称:" + C.GoString(str),
        Desc: "描述:" + C.GoString(str),
    }
    var x C.ctx_info
    x.name = C.CString(info.Name)
    x.desc = C.CString(info.Desc)
    return x
}

//export GetLangs
func GetLangs() C.langs {
    l := Langs{Name: "Golang",Num: 1}
//    fmt.Println(l)
    var lang C.langs
    lang.name = C.CString(l.Name)
    lang.num = C.int(l.Num)
    return lang
}

//export GetErr
func GetErr(x bool) string {
    if x {
        return errors.New("测试错误类型").Error()
    }
    return ""
}

type MyPoint struct {
    Name string
    X    int
    Y    int
}

type MyInfo struct {
    Name string
    Desc string
}

type Langs struct {
    Name string
    Num int
}

func (l *Langs) RP(p C.langs)  {
    //    fmt.Println(p)
    l.Name = C.GoString(p.name)
    fmt.Println(reflect.ValueOf(p.num).Type())
    //l.Num,_ = strconv.Atoi(fmt.Sprintf("%d",p.num))
    l.Num  = int(p.num)
}