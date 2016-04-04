; ModuleID = 'pointerO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"%d %d %d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %p = alloca i32*, align 8
  %q = alloca i32*, align 8
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %e = alloca i32, align 4
  store i32 1, i32* %a, align 4
  store i32* %a, i32** %p, align 8
  store i32* %b, i32** %q, align 8
  store i32 2, i32* %b, align 4
  %0 = load i32, i32* %a, align 4
  %1 = load i32*, i32** %p, align 8
  %2 = load i32, i32* %1, align 4
  %add = add nsw i32 %0, %2
  store i32 %add, i32* %c, align 4
  %3 = load i32*, i32** %q, align 8
  %4 = load i32, i32* %3, align 4
  %5 = load i32, i32* %b, align 4
  %add1 = add nsw i32 %4, %5
  store i32 %add1, i32* %d, align 4
  %6 = load i32*, i32** %q, align 8
  %7 = load i32, i32* %6, align 4
  %8 = load i32*, i32** %p, align 8
  %9 = load i32, i32* %8, align 4
  %mul = mul nsw i32 %7, %9
  store i32 %mul, i32* %e, align 4
  %10 = load i32, i32* %c, align 4
  %11 = load i32, i32* %d, align 4
  %12 = load i32, i32* %e, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i32 %10, i32 %11, i32 %12)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
