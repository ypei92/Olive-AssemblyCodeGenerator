; ModuleID = 'arithmetic.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  %d = alloca i64, align 8
  %e = alloca i64, align 8
  store i32 0, i32* %retval, align 4
  store i64 7, i64* %a, align 8
  store i64 3, i64* %b, align 8
  store i64 8, i64* %c, align 8
  store i64 2, i64* %d, align 8
  store i64 -9, i64* %e, align 8
  %0 = load i64, i64* %a, align 8
  %1 = load i64, i64* %b, align 8
  %add = add nsw i64 %0, %1
  %2 = load i64, i64* %d, align 8
  %div = sdiv i64 %add, %2
  %3 = load i64, i64* %e, align 8
  %mul = mul nsw i64 %div, %3
  %4 = load i64, i64* %c, align 8
  %sub = sub nsw i64 %mul, %4
  %add1 = add nsw i64 %sub, -4
  %mul2 = mul nsw i64 %add1, -1
  %conv = trunc i64 %mul2 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
