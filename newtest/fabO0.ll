; ModuleID = 'fabO0.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [6 x i8] c"%lld\0A\00", align 1

; Function Attrs: nounwind uwtable
define i64 @fact(i64 %a) #0 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca i64, align 8
  store i64 %a, i64* %a.addr, align 8
  %0 = load i64, i64* %a.addr, align 8
  %cmp = icmp eq i64 %0, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 1, i64* %retval, align 8
  br label %return

if.else:                                          ; preds = %entry
  %1 = load i64, i64* %a.addr, align 8
  %cmp1 = icmp eq i64 %1, 1
  br i1 %cmp1, label %if.then2, label %if.end

if.then2:                                         ; preds = %if.else
  store i64 1, i64* %retval, align 8
  br label %return

if.end:                                           ; preds = %if.else
  br label %if.end3

if.end3:                                          ; preds = %if.end
  %2 = load i64, i64* %a.addr, align 8
  %sub = sub nsw i64 %2, 1
  %call = call i64 @fact(i64 %sub)
  %3 = load i64, i64* %a.addr, align 8
  %sub4 = sub nsw i64 %3, 2
  %call5 = call i64 @fact(i64 %sub4)
  %add = add nsw i64 %call, %call5
  store i64 %add, i64* %retval, align 8
  br label %return

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %4 = load i64, i64* %retval, align 8
  ret i64 %4
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i64, align 8
  %b = alloca i64, align 8
  store i64 4, i64* %a, align 8
  %0 = load i64, i64* %a, align 8
  %call = call i64 @fact(i64 %0)
  store i64 %call, i64* %b, align 8
  %1 = load i64, i64* %b, align 8
  %call1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i64 %1)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 "}
