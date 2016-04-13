; ModuleID = 'recursion.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @factorial(i64 %a) #0 {
entry:
  %cmp = icmp eq i64 %a, 1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  br label %return

if.else:                                          ; preds = %entry
  %sub = sub nsw i64 %a, 1
  %call = call i64 @factorial(i64 %sub)
  %mul = mul nsw i64 %a, %call
  br label %return

return:                                           ; preds = %if.else, %if.then
  %retval.0 = phi i64 [ 1, %if.then ], [ %mul, %if.else ]
  ret i64 %retval.0
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %call = call i64 @factorial(i64 5)
  %conv = trunc i64 %call to i32
  ret i32 %conv
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
