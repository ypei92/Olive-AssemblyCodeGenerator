; ModuleID = 'condition1.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  %c = alloca i64, align 8
  store i32 0, i32* %retval, align 4
  store i64 3, i64* %a, align 8
  store i64 4, i64* %b, align 8
  store i64 0, i64* %c, align 8
  %0 = load i64, i64* %a, align 8
  %cmp = icmp slt i64 %0, 10
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 4, i64* %c, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  store i64 2, i64* %c, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %1 = load i64, i64* %b, align 8
  %cmp1 = icmp sgt i64 %1, 5
  br i1 %cmp1, label %if.then2, label %if.else3

if.then2:                                         ; preds = %if.end
  %2 = load i64, i64* %c, align 8
  %inc = add nsw i64 %2, 1
  store i64 %inc, i64* %c, align 8
  br label %if.end8

if.else3:                                         ; preds = %if.end
  %3 = load i64, i64* %b, align 8
  %cmp4 = icmp sgt i64 %3, 3
  br i1 %cmp4, label %if.then5, label %if.else6

if.then5:                                         ; preds = %if.else3
  %4 = load i64, i64* %c, align 8
  %add = add nsw i64 %4, 4
  store i64 %add, i64* %c, align 8
  br label %if.end7

if.else6:                                         ; preds = %if.else3
  store i64 7, i64* %c, align 8
  br label %if.end7

if.end7:                                          ; preds = %if.else6, %if.then5
  br label %if.end8

if.end8:                                          ; preds = %if.end7, %if.then2
  %5 = load i64, i64* %a, align 8
  %cmp9 = icmp slt i64 %5, 10
  br i1 %cmp9, label %land.lhs.true, label %if.end13

land.lhs.true:                                    ; preds = %if.end8
  %6 = load i64, i64* %b, align 8
  %cmp10 = icmp sgt i64 %6, 3
  br i1 %cmp10, label %if.then11, label %if.end13

if.then11:                                        ; preds = %land.lhs.true
  %7 = load i64, i64* %c, align 8
  %inc12 = add nsw i64 %7, 1
  store i64 %inc12, i64* %c, align 8
  br label %if.end13

if.end13:                                         ; preds = %if.then11, %land.lhs.true, %if.end8
  %8 = load i64, i64* %a, align 8
  %cmp14 = icmp sgt i64 %8, 10
  br i1 %cmp14, label %if.then15, label %if.else16

if.then15:                                        ; preds = %if.end13
  store i64 -90, i64* %c, align 8
  br label %if.end18

if.else16:                                        ; preds = %if.end13
  %9 = load i64, i64* %c, align 8
  %10 = load i64, i64* %a, align 8
  %add17 = add nsw i64 %9, %10
  store i64 %add17, i64* %c, align 8
  br label %if.end18

if.end18:                                         ; preds = %if.else16, %if.then15
  %11 = load i64, i64* %c, align 8
  %conv = trunc i64 %11 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
