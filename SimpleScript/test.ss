#function Helo
decl(helo){
    print(1);
    call(func2);
}

#function func2
decl(func2){
    print(2)
    call(helo);
}

call(helo);
exit();
