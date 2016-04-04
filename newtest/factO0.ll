; ModuleID = 'factO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @fact(i32 %a) #0 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  %0 = load i32, i32* %a.addr, align 4
  %cmp = icmp eq i32 %0, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4
  br label %return

if.else:                                          ; preds = %entry
  %1 = load i32, i32* %a.addr, align 4
  %cmp1 = icmp eq i32 %1, 1
  br i1 %cmp1, label %if.then2, label %if.end

if.then2:                                         ; preds = %if.else
  store i32 1, i32* %retval, align 4
  br label %return

if.end:                                           ; preds = %if.else
  br label %if.end3

if.end3:                                          ; preds = %if.end
  %2 = load i32, i32* %a.addr, align 4
  %sub = sub nsw i32 %2, 1
  %call = call i32 @fact(i32 %sub)
  %3 = load i32, i32* %a.addr, align 4
  %sub4 = sub nsw i32 %3, 2
  %call5 = call i32 @fact(i32 %sub4)
  %add = add nsw i32 %call, %call5
  store i32 %add, i32* %retval, align 4
  br label %return

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %4 = load i32, i32* %retval, align 4
  ret i32 %4
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 4, i32* %a, align 4
  %0 = load i32, i32* %a, align 4
  %call = call i32 @fact(i32 %0)
  store i32 %call, i32* %b, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
