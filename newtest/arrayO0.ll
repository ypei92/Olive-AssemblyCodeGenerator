; ModuleID = 'arrayO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %d = alloca [4 x i32], align 16
  store i32 0, i32* %a, align 4
  store i32 2, i32* %b, align 4
  %0 = load i32, i32* %a, align 4
  %arrayidx = getelementptr inbounds [4 x i32], [4 x i32]* %d, i64 0, i64 0
  store i32 %0, i32* %arrayidx, align 16
  %1 = load i32, i32* %b, align 4
  %arrayidx1 = getelementptr inbounds [4 x i32], [4 x i32]* %d, i64 0, i64 1
  store i32 %1, i32* %arrayidx1, align 4
  %2 = load i32, i32* %a, align 4
  %3 = load i32, i32* %b, align 4
  %add = add nsw i32 %2, %3
  %arrayidx2 = getelementptr inbounds [4 x i32], [4 x i32]* %d, i64 0, i64 2
  store i32 %add, i32* %arrayidx2, align 8
  %4 = load i32, i32* %a, align 4
  %5 = load i32, i32* %b, align 4
  %sub = sub nsw i32 %4, %5
  %arrayidx3 = getelementptr inbounds [4 x i32], [4 x i32]* %d, i64 0, i64 3
  store i32 %sub, i32* %arrayidx3, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
