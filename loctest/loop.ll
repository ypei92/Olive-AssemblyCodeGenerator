; ModuleID = 'loop.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  %i = alloca i64, align 8
  %d = alloca i64, align 8
  store i32 0, i32* %retval, align 4
  store i64 3, i64* %a, align 8
  store i64 4, i64* %b, align 8
  store i64 0, i64* %c, align 8
  store i64 0, i64* %i, align 8
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8
  %1 = load i64, i64* %a, align 8
  %cmp = icmp slt i64 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load i64, i64* %c, align 8
  %add = add nsw i64 %2, 2
  store i64 %add, i64* %c, align 8
  %3 = load i64, i64* %i, align 8
  %cmp1 = icmp eq i64 %3, 1
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %for.body
  br label %for.end

if.end:                                           ; preds = %for.body
  br label %for.inc

for.inc:                                          ; preds = %if.end
  %4 = load i64, i64* %i, align 8
  %inc = add nsw i64 %4, 1
  store i64 %inc, i64* %i, align 8
  br label %for.cond

for.end:                                          ; preds = %if.then, %for.cond
  store i64 0, i64* %d, align 8
  br label %while.cond

while.cond:                                       ; preds = %if.end6, %if.then5, %for.end
  %5 = load i64, i64* %d, align 8
  %cmp2 = icmp slt i64 %5, 4
  br i1 %cmp2, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %6 = load i64, i64* %d, align 8
  %inc3 = add nsw i64 %6, 1
  store i64 %inc3, i64* %d, align 8
  %7 = load i64, i64* %d, align 8
  %cmp4 = icmp sle i64 %7, 2
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %while.body
  br label %while.cond

if.end6:                                          ; preds = %while.body
  %8 = load i64, i64* %c, align 8
  %add7 = add nsw i64 %8, 3
  store i64 %add7, i64* %c, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %9 = load i64, i64* %c, align 8
  %conv = trunc i64 %9 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
