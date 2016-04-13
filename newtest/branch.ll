; ModuleID = 'branch.bc'
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
  store i64 1, i64* %a, align 8
  store i64 2, i64* %b, align 8
  store i64 0, i64* %c, align 8
  %0 = load i64, i64* %a, align 8
  %1 = load i64, i64* %b, align 8
  %cmp = icmp sgt i64 %0, %1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %b, align 8
  store i64 %2, i64* %c, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  %3 = load i64, i64* %a, align 8
  store i64 %3, i64* %c, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %4 = load i32, i32* %retval, align 4
  ret i32 %4
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.0 (http://llvm.org/git/clang.git e88720a6287e5fa399e833ed5ddf4f0b475c37bd) (http://llvm.org/git/llvm.git 9867695c88ba0998618aa879e86315800c49c7c8)"}
