; ModuleID = 'loopO1.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [13 x i8] c"%d %d %d %d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
while.body.preheader:
  br label %while.cond.loopexit.thread

while.cond.loopexit.thread:                       ; preds = %while.body.preheader, %while.cond.loopexit.thread
  %dec451 = phi i32 [ 2, %while.body.preheader ], [ %dec4, %while.cond.loopexit.thread ]
  %dec50 = phi i32 [ 1, %while.body.preheader ], [ %dec, %while.cond.loopexit.thread ]
  %inc349 = phi i32 [ 2, %while.body.preheader ], [ %inc3, %while.cond.loopexit.thread ]
  %d.03748 = phi i32 [ 0, %while.body.preheader ], [ %1, %while.cond.loopexit.thread ]
  %indvars.iv47 = phi i32 [ 2, %while.body.preheader ], [ %indvars.iv.next46, %while.cond.loopexit.thread ]
  %0 = icmp sgt i32 %indvars.iv47, 1
  %smax = select i1 %0, i32 %indvars.iv47, i32 1
  %1 = add i32 %d.03748, %smax
  %indvars.iv.next46 = add i32 %indvars.iv47, -1
  %inc3 = add nuw nsw i32 %inc349, 1
  %dec = add nsw i32 %dec50, -1
  %dec4 = add nsw i32 %dec451, -1
  %cmp730 = icmp sgt i32 %dec451, 1
  br i1 %cmp730, label %while.cond.loopexit.thread, label %while.end

while.end:                                        ; preds = %while.cond.loopexit.thread
  %call = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i64 0, i64 0), i32 %inc3, i32 %dec, i32 %dec4, i32 %1)
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
