; ModuleID = 'call_call.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @foo(i64 %a, i64 %b, i64 %c, i64 %d, i64 %e, i64 %f, i64 %g, i64 %h, i64 %i) #0 {
entry:
  %a.addr = alloca i64, align 8
  %b.addr = alloca i64, align 8
  %c.addr = alloca i64, align 8
  %d.addr = alloca i64, align 8
  %e.addr = alloca i64, align 8
  %f.addr = alloca i64, align 8
  %g.addr = alloca i64, align 8
  %h.addr = alloca i64, align 8
  %i.addr = alloca i64, align 8
  store i64 %a, i64* %a.addr, align 8
  store i64 %b, i64* %b.addr, align 8
  store i64 %c, i64* %c.addr, align 8
  store i64 %d, i64* %d.addr, align 8
  store i64 %e, i64* %e.addr, align 8
  store i64 %f, i64* %f.addr, align 8
  store i64 %g, i64* %g.addr, align 8
  store i64 %h, i64* %h.addr, align 8
  store i64 %i, i64* %i.addr, align 8
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
  %8 = load i64, i64* %i.addr, align 8
  %add7 = add nsw i64 %add6, %8
  ret i64 %add7
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  %d = alloca i64, align 8
  %e = alloca i64, align 8
  %f = alloca i64, align 8
  %g = alloca i64, align 8
  %h = alloca i64, align 8
  %i = alloca i64, align 8
  %res = alloca i64, align 8
  %res1 = alloca i64, align 8
  store i64 1, i64* %a, align 8
  store i64 2, i64* %b, align 8
  store i64 3, i64* %c, align 8
  store i64 4, i64* %d, align 8
  store i64 5, i64* %e, align 8
  store i64 6, i64* %f, align 8
  store i64 7, i64* %g, align 8
  store i64 8, i64* %h, align 8
  store i64 9, i64* %i, align 8
  %0 = load i64, i64* %a, align 8
  %1 = load i64, i64* %b, align 8
  %2 = load i64, i64* %c, align 8
  %3 = load i64, i64* %d, align 8
  %4 = load i64, i64* %e, align 8
  %5 = load i64, i64* %f, align 8
  %6 = load i64, i64* %g, align 8
  %7 = load i64, i64* %h, align 8
  %8 = load i64, i64* %i, align 8
  %call = call i64 @foo(i64 %0, i64 %1, i64 %2, i64 %3, i64 %4, i64 %5, i64 %6, i64 %7, i64 %8)
  store i64 %call, i64* %res, align 8
  %9 = load i64, i64* %i, align 8
  %10 = load i64, i64* %h, align 8
  %11 = load i64, i64* %g, align 8
  %12 = load i64, i64* %f, align 8
  %13 = load i64, i64* %e, align 8
  %14 = load i64, i64* %d, align 8
  %15 = load i64, i64* %c, align 8
  %16 = load i64, i64* %b, align 8
  %17 = load i64, i64* %a, align 8
  %call1 = call i64 @foo(i64 %9, i64 %10, i64 %11, i64 %12, i64 %13, i64 %14, i64 %15, i64 %16, i64 %17)
  store i64 %call1, i64* %res1, align 8
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
