; ModuleID = 'manyArgs.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @stuff(i64 %a, i64 %b, i64 %c, i64 %d, i64 %e, i64 %f, i64 %g, i64 %h, i64 %j) #0 {
entry:
  %a.addr = alloca i64, align 8
  %b.addr = alloca i64, align 8
  %c.addr = alloca i64, align 8
  %d.addr = alloca i64, align 8
  %e.addr = alloca i64, align 8
  %f.addr = alloca i64, align 8
  %g.addr = alloca i64, align 8
  %h.addr = alloca i64, align 8
  %j.addr = alloca i64, align 8
  store i64 %a, i64* %a.addr, align 8
  store i64 %b, i64* %b.addr, align 8
  store i64 %c, i64* %c.addr, align 8
  store i64 %d, i64* %d.addr, align 8
  store i64 %e, i64* %e.addr, align 8
  store i64 %f, i64* %f.addr, align 8
  store i64 %g, i64* %g.addr, align 8
  store i64 %h, i64* %h.addr, align 8
  store i64 %j, i64* %j.addr, align 8
  %0 = load i64, i64* %a.addr, align 8
  %1 = load i64, i64* %b.addr, align 8
  %add = add nsw i64 %0, %1
  %2 = load i64, i64* %c.addr, align 8
  %add1 = add nsw i64 %add, %2
  %3 = load i64, i64* %d.addr, align 8
  %add2 = add nsw i64 %add1, %3
  %4 = load i64, i64* %e.addr, align 8
  %add3 = add nsw i64 %add2, %4
  %5 = load i64, i64* %f.addr, align 8
  %add4 = add nsw i64 %add3, %5
  %6 = load i64, i64* %g.addr, align 8
  %add5 = add nsw i64 %add4, %6
  %7 = load i64, i64* %h.addr, align 8
  %add6 = add nsw i64 %add5, %7
  %8 = load i64, i64* %j.addr, align 8
  %add7 = add nsw i64 %add6, %8
  ret i64 %add7
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %k = alloca i64, align 8
  store i32 0, i32* %retval, align 4
  %call = call i64 @stuff(i64 1, i64 1, i64 1, i64 1, i64 1, i64 1, i64 2, i64 2, i64 2)
  store i64 %call, i64* %k, align 8
  %0 = load i64, i64* %k, align 8
  %conv = trunc i64 %0 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
