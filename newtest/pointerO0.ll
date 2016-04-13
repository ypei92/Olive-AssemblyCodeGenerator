; ModuleID = 'pointerO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %p = alloca i64*, align 8
  %q = alloca i64*, align 8
  %g = alloca i64, align 8
  %c = alloca i64, align 8
  %d = alloca i64, align 8
  %e = alloca i64, align 8
  store i64 1, i64* %a, align 8
  store i64* %a, i64** %p, align 8
  store i64* %b, i64** %q, align 8
  store i64 2, i64* %b, align 8
  %0 = load i64, i64* %a, align 8
  store i64 %0, i64* %g, align 8
  %1 = load i64, i64* %a, align 8
  %2 = load i64*, i64** %p, align 8
  %3 = load i64, i64* %2, align 8
  %add = add nsw i64 %1, %3
  store i64 %add, i64* %c, align 8
  %4 = load i64*, i64** %q, align 8
  %5 = load i64, i64* %4, align 8
  %6 = load i64, i64* %b, align 8
  %add1 = add nsw i64 %5, %6
  store i64 %add1, i64* %d, align 8
  %7 = load i64*, i64** %q, align 8
  %8 = load i64, i64* %7, align 8
  %9 = load i64*, i64** %p, align 8
  %10 = load i64, i64* %9, align 8
  %add2 = add nsw i64 %8, %10
  store i64 %add2, i64* %e, align 8
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
