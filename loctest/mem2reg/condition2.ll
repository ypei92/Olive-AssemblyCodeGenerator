; ModuleID = 'condition2.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %cmp = icmp slt i64 3, 10
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %add = add nsw i64 0, 1
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %c.0 = phi i64 [ %add, %if.then ], [ 0, %entry ]
  %cmp1 = icmp sgt i64 3, 2
  br i1 %cmp1, label %if.then2, label %if.end4

if.then2:                                         ; preds = %if.end
  %add3 = add nsw i64 %c.0, 1
  br label %if.end4

if.end4:                                          ; preds = %if.then2, %if.end
  %c.1 = phi i64 [ %add3, %if.then2 ], [ %c.0, %if.end ]
  %cmp5 = icmp sge i64 3, 3
  br i1 %cmp5, label %if.then6, label %if.end8

if.then6:                                         ; preds = %if.end4
  %add7 = add nsw i64 %c.1, 1
  br label %if.end8

if.end8:                                          ; preds = %if.then6, %if.end4
  %c.2 = phi i64 [ %add7, %if.then6 ], [ %c.1, %if.end4 ]
  %cmp9 = icmp sle i64 3, 3
  br i1 %cmp9, label %if.then10, label %if.end12

if.then10:                                        ; preds = %if.end8
  %add11 = add nsw i64 %c.2, 1
  br label %if.end12

if.end12:                                         ; preds = %if.then10, %if.end8
  %c.3 = phi i64 [ %add11, %if.then10 ], [ %c.2, %if.end8 ]
  %cmp13 = icmp sle i64 3, 4
  br i1 %cmp13, label %if.then14, label %if.end16

if.then14:                                        ; preds = %if.end12
  %add15 = add nsw i64 %c.3, 1
  br label %if.end16

if.end16:                                         ; preds = %if.then14, %if.end12
  %c.4 = phi i64 [ %add15, %if.then14 ], [ %c.3, %if.end12 ]
  %cmp17 = icmp sge i64 3, 2
  br i1 %cmp17, label %if.then18, label %if.end20

if.then18:                                        ; preds = %if.end16
  %add19 = add nsw i64 %c.4, 1
  br label %if.end20

if.end20:                                         ; preds = %if.then18, %if.end16
  %c.5 = phi i64 [ %add19, %if.then18 ], [ %c.4, %if.end16 ]
  %cmp21 = icmp eq i64 3, 3
  br i1 %cmp21, label %if.then22, label %if.end24

if.then22:                                        ; preds = %if.end20
  %add23 = add nsw i64 %c.5, 1
  br label %if.end24

if.end24:                                         ; preds = %if.then22, %if.end20
  %c.6 = phi i64 [ %add23, %if.then22 ], [ %c.5, %if.end20 ]
  %cmp25 = icmp ne i64 3, 2
  br i1 %cmp25, label %if.then26, label %if.end28

if.then26:                                        ; preds = %if.end24
  %add27 = add nsw i64 %c.6, 1
  br label %if.end28

if.end28:                                         ; preds = %if.then26, %if.end24
  %c.7 = phi i64 [ %add27, %if.then26 ], [ %c.6, %if.end24 ]
  %cmp29 = icmp eq i64 3, 2
  br i1 %cmp29, label %if.end32, label %if.then30

if.then30:                                        ; preds = %if.end28
  %add31 = add nsw i64 %c.7, 1
  br label %if.end32

if.end32:                                         ; preds = %if.then30, %if.end28
  %c.8 = phi i64 [ %c.7, %if.end28 ], [ %add31, %if.then30 ]
  %conv = trunc i64 %c.8 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
