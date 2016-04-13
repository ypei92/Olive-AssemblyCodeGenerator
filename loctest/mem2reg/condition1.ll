; ModuleID = 'condition1.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %cmp = icmp slt i64 3, 10
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %c.0 = phi i64 [ 4, %if.then ], [ 2, %if.else ]
  %cmp1 = icmp sgt i64 4, 5
  br i1 %cmp1, label %if.then2, label %if.else3

if.then2:                                         ; preds = %if.end
  %inc = add nsw i64 %c.0, 1
  br label %if.end8

if.else3:                                         ; preds = %if.end
  %cmp4 = icmp sgt i64 4, 3
  br i1 %cmp4, label %if.then5, label %if.else6

if.then5:                                         ; preds = %if.else3
  %add = add nsw i64 %c.0, 4
  br label %if.end7

if.else6:                                         ; preds = %if.else3
  br label %if.end7

if.end7:                                          ; preds = %if.else6, %if.then5
  %c.1 = phi i64 [ %add, %if.then5 ], [ 7, %if.else6 ]
  br label %if.end8

if.end8:                                          ; preds = %if.end7, %if.then2
  %c.2 = phi i64 [ %inc, %if.then2 ], [ %c.1, %if.end7 ]
  %cmp9 = icmp slt i64 3, 10
  br i1 %cmp9, label %land.lhs.true, label %if.end13

land.lhs.true:                                    ; preds = %if.end8
  %cmp10 = icmp sgt i64 4, 3
  br i1 %cmp10, label %if.then11, label %if.end13

if.then11:                                        ; preds = %land.lhs.true
  %inc12 = add nsw i64 %c.2, 1
  br label %if.end13

if.end13:                                         ; preds = %if.then11, %land.lhs.true, %if.end8
  %c.3 = phi i64 [ %inc12, %if.then11 ], [ %c.2, %land.lhs.true ], [ %c.2, %if.end8 ]
  %cmp14 = icmp sgt i64 3, 10
  br i1 %cmp14, label %if.then15, label %if.else16

if.then15:                                        ; preds = %if.end13
  br label %if.end18

if.else16:                                        ; preds = %if.end13
  %add17 = add nsw i64 %c.3, 3
  br label %if.end18

if.end18:                                         ; preds = %if.else16, %if.then15
  %c.4 = phi i64 [ -90, %if.then15 ], [ %add17, %if.else16 ]
  %conv = trunc i64 %c.4 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
