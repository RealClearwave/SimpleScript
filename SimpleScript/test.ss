a[11] = 0
for(&i,1,10){
	a[i] = input()
}

s = 0
for(&i,1,10){
	s = add(s,a[i])
	println(i);
}

println(s);