; ModuleID = 'loop.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %c.0 = phi i64 [ 0, %entry ], [ %add, %for.inc ]
  %i.0 = phi i64 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i64 %i.0, 3
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %add = add nsw i64 %c.0, 2
  %cmp1 = icmp eq i64 %i.0, 1
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %for.body
  br label %for.end

if.end:                                           ; preds = %for.body
  br label %for.inc

for.inc:                                          ; preds = %if.end
  %inc = add nsw i64 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %if.then, %for.cond
  %c.1 = phi i64 [ %add, %if.then ], [ %c.0, %for.cond ]
  br label %while.cond

while.cond:                                       ; preds = %if.end6, %if.then5, %for.end
  %c.2 = phi i64 [ %c.1, %for.end ], [ %c.2, %if.then5 ], [ %add7, %if.end6 ]
  %d.0 = phi i64 [ 0, %for.end ], [ %inc3, %if.then5 ], [ %inc3, %if.end6 ]
  %cmp2 = icmp slt i64 %d.0, 4
  br i1 %cmp2, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %inc3 = add nsw i64 %d.0, 1
  %cmp4 = icmp sle i64 %inc3, 2
  br i1 %cmp4, label %if.then5, label %if.end6

if.then5:                                         ; preds = %while.body
  br label %while.cond

if.end6:                                          ; preds = %while.body
  %add7 = add nsw i64 %c.2, 3
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %conv = trunc i64 %c.2 to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
