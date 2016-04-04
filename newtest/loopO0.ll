; ModuleID = 'loopO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [13 x i8] c"%d %d %d %d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %i = alloca i32, align 4
  %i5 = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 1, i32* %a, align 4
  store i32 2, i32* %b, align 4
  store i32 0, i32* %c, align 4
  store i32 0, i32* %d, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4
  %1 = load i32, i32* %a, align 4
  %2 = load i32, i32* %b, align 4
  %add = add nsw i32 %1, %2
  %cmp = icmp slt i32 %0, %add
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load i32, i32* %c, align 4
  %inc = add nsw i32 %3, 1
  store i32 %inc, i32* %c, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32, i32* %i, align 4
  %inc1 = add nsw i32 %4, 1
  store i32 %inc1, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  br label %while.cond

while.cond:                                       ; preds = %for.end12, %for.end
  %5 = load i32, i32* %c, align 4
  %cmp2 = icmp sgt i32 %5, 0
  br i1 %cmp2, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %6 = load i32, i32* %a, align 4
  %inc3 = add nsw i32 %6, 1
  store i32 %inc3, i32* %a, align 4
  %7 = load i32, i32* %b, align 4
  %dec = add nsw i32 %7, -1
  store i32 %dec, i32* %b, align 4
  %8 = load i32, i32* %c, align 4
  %dec4 = add nsw i32 %8, -1
  store i32 %dec4, i32* %c, align 4
  store i32 0, i32* %i5, align 4
  br label %for.cond6

for.cond6:                                        ; preds = %for.inc10, %while.body
  %9 = load i32, i32* %i5, align 4
  %10 = load i32, i32* %c, align 4
  %cmp7 = icmp slt i32 %9, %10
  br i1 %cmp7, label %for.body8, label %for.end12

for.body8:                                        ; preds = %for.cond6
  %11 = load i32, i32* %d, align 4
  %inc9 = add nsw i32 %11, 1
  store i32 %inc9, i32* %d, align 4
  br label %for.inc10

for.inc10:                                        ; preds = %for.body8
  %12 = load i32, i32* %i5, align 4
  %inc11 = add nsw i32 %12, 1
  store i32 %inc11, i32* %i5, align 4
  br label %for.cond6

for.end12:                                        ; preds = %for.cond6
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %13 = load i32, i32* %a, align 4
  %14 = load i32, i32* %b, align 4
  %15 = load i32, i32* %c, align 4
  %16 = load i32, i32* %d, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i32 %13, i32 %14, i32 %15, i32 %16)
  %17 = load i32, i32* %retval, align 4
  ret i32 %17
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
