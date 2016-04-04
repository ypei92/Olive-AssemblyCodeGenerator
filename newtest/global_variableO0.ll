; ModuleID = 'global_variableO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@d = global i32 20, align 4
@e = global i64 30, align 8
@f = global i64 40, align 8
@.str = private unnamed_addr constant [13 x i8] c"%d %ld %lld\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 2, i32* %b, align 4
  store i32 3, i32* %c, align 4
  %0 = load i32, i32* %a, align 4
  %1 = load i32, i32* @d, align 4
  %add = add nsw i32 %0, %1
  store i32 %add, i32* @d, align 4
  %2 = load i32, i32* %b, align 4
  %conv = sext i32 %2 to i64
  %3 = load i64, i64* @e, align 8
  %add1 = add nsw i64 %conv, %3
  store i64 %add1, i64* @e, align 8
  %4 = load i32, i32* %c, align 4
  %conv2 = sext i32 %4 to i64
  %5 = load i64, i64* @f, align 8
  %add3 = add nsw i64 %conv2, %5
  store i64 %add3, i64* @f, align 8
  %6 = load i32, i32* @d, align 4
  %7 = load i64, i64* @e, align 8
  %8 = load i64, i64* @f, align 8
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i32 %6, i64 %7, i64 %8)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
