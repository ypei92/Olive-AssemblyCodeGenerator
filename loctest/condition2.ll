; ModuleID = 'condition2.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i64, align 8
  %c = alloca i64, align 8
  store i32 0, i32* %retval, align 4
  store i64 3, i64* %a, align 8
  store i64 0, i64* %c, align 8
  %0 = load i64, i64* %a, align 8
  %cmp = icmp slt i64 %0, 10
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %c, align 8
  %add = add nsw i64 %1, 1
  store i64 %add, i64* %c, align 8
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %2 = load i64, i64* %a, align 8
  %cmp1 = icmp sgt i64 %2, 2
  br i1 %cmp1, label %if.then2, label %if.end4

if.then2:                                         ; preds = %if.end
  %3 = load i64, i64* %c, align 8
  %add3 = add nsw i64 %3, 1
  store i64 %add3, i64* %c, align 8
  br label %if.end4

if.end4:                                          ; preds = %if.then2, %if.end
  %4 = load i64, i64* %a, align 8
  %cmp5 = icmp sge i64 %4, 3
  br i1 %cmp5, label %if.then6, label %if.end8

if.then6:                                         ; preds = %if.end4
  %5 = load i64, i64* %c, align 8
  %add7 = add nsw i64 %5, 1
  store i64 %add7, i64* %c, align 8
  br label %if.end8

if.end8:                                          ; preds = %if.then6, %if.end4
  %6 = load i64, i64* %a, align 8
  %cmp9 = icmp sle i64 %6, 3
  br i1 %cmp9, label %if.then10, label %if.end12

if.then10:                                        ; preds = %if.end8
  %7 = load i64, i64* %c, align 8
  %add11 = add nsw i64 %7, 1
  store i64 %add11, i64* %c, align 8
  br label %if.end12

if.end12:                                         ; preds = %if.then10, %if.end8
  %8 = load i64, i64* %a, align 8
  %cmp13 = icmp sle i64 %8, 4
  br i1 %cmp13, label %if.then14, label %if.end16

if.then14:                                        ; preds = %if.end12
  %9 = load i64, i64* %c, align 8
  %add15 = add nsw i64 %9, 1
  store i64 %add15, i64* %c, align 8
  br label %if.end16

if.end16:                                         ; preds = %if.then14, %if.end12
  %10 = load i64, i64* %a, align 8
  %cmp17 = icmp sge i64 %10, 2
  br i1 %cmp17, label %if.then18, label %if.end20

if.then18:                                        ; preds = %if.end16
  %11 = load i64, i64* %c, align 8
  %add19 = add nsw i64 %11, 1
  store i64 %add19, i64* %c, align 8
  br label %if.end20

if.end20:                                         ; preds = %if.then18, %if.end16
  %12 = load i64, i64* %a, align 8
  %cmp21 = icmp eq i64 %12, 3
  br i1 %cmp21, label %if.then22, label %if.end24

if.then22:                                        ; preds = %if.end20
  %13 = load i64, i64* %c, align 8
  %add23 = add nsw i64 %13, 1
  store i64 %add23, i64* %c, align 8
  br label %if.end24

if.end24:                                         ; preds = %if.then22, %if.end20
  %14 = load i64, i64* %a, align 8
  %cmp25 = icmp ne i64 %14, 2
  br i1 %cmp25, label %if.then26, label %if.end28

if.then26:                                        ; preds = %if.end24
  %15 = load i64, i64* %c, align 8
  %add27 = add nsw i64 %15, 1
  store i64 %add27, i64* %c, align 8
  br label %if.end28

if.end28:                                         ; preds = %if.then26, %if.end24
  %16 = load i64, i64* %a, align 8
  %cmp29 = icmp eq i64 %16, 2
  br i1 %cmp29, label %if.end32, label %if.then30

if.then30:                                        ; preds = %if.end28
  %17 = load i64, i64* %c, align 8
  %add31 = add nsw i64 %17, 1
  store i64 %add31, i64* %c, align 8
  br label %if.end32

if.end32:                                         ; preds = %if.then30, %if.end28
  %18 = load i64, i64* %c, align 8
  %conv = trunc i64 %18 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
