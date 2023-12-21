package main
import "fmt"
type nest struct{
	field int
}
type mystruct struct{
	myfield int
	nested nest 
}
func main(){
	structinst := mystruct{42,nest{23}}
	fmt.Println(structinst)
}