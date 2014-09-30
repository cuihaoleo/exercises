program numbeng;
var n,a,b:longint; {English n:number,a:thousand,b:million}
begin
readln(n);

if n<0 then write('negative ');

if n=0 then write('zero');

n:=abs(n);

if n>999999 then
begin
  b:=n div 1000000;
  case b of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
   10:write('ten');
   11:write('eleven');
   12:write('twelve');
   13:write('thirteen');
   14:write('fourteen');
   15:write('fifteen');
   16:write('sixteen');
   17:write('seventeen');
   18:write('eighteen');
   19:write('nineteen');
  end; {0-19}

if (b>19)and(b<100) then {20-100}
begin
  case b div 10 of
   2:write('twenty');
   3:write('thirty');
   4:write('forty');
   5:write('fifty');
   6:write('sixty');
   7:write('seventy');
   8:write('eighty');
   9:write('ninety');
  end;
  case b mod 10 of
   1:write('-one');
   2:write('-two');
   3:write('-three');
   4:write('-four');
   5:write('-five');
   6:write('-six');
   7:write('-seven');
   8:write('-eight');
   9:write('-nine');
  end;
end; {20-100}

if (b>99)and(b<1000) then {999-1000}
begin
  if b mod 100=0 then
  begin
  case b div 100 of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
  end;
  write(' hundred');
  end
  else
  begin
  case b div 100 of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
  end;
  write(' hundred and ');
  case (b mod 100)-(b mod 10) of
   20:write('twenty');
   30:write('thirty');
   40:write('forty');
   50:write('fifty');
   60:write('sixty');
   70:write('seventy');
   80:write('eighty');
   90:write('ninety');
  end;
  if b mod 100<20 then
  begin
   case b mod 100 of
    1:write('one');
    2:write('two');
    3:write('three');
    4:write('four');
    5:write('five');
    6:write('six');
    7:write('seven');
    8:write('eight');
    9:write('nine');
    10:write('ten');
    11:write('eleven');
    12:write('twelve');
    13:write('thirteen');
    14:write('fourteen');
    15:write('fifteen');
    16:write('sixteen');
    17:write('seventeen');
    18:write('eighteen');
    19:write('nineteen');
   end;
  end
  else
  begin
   case b mod 10 of
    1:write('-one');
    2:write('-two');
    3:write('-three');
    4:write('-four');
    5:write('-five');
    6:write('-six');
    7:write('-seven');
    8:write('-eight');
    9:write('-nine');
    end;
   end;
  end;
end; {999-1000}
end;

if n>999999
then
begin
write(' million ');
n:=n-1000000*b;

if (n<100000) and (n>0)
then
  write('and ');
end;



if n>999 then
begin
   a:=n div 1000;
  case a of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
   10:write('ten');
   11:write('eleven');
   12:write('twelve');
   13:write('thirteen');
   14:write('fourteen');
   15:write('fifteen');
   16:write('sixteen');
   17:write('seventeen');
   18:write('eighteen');
   19:write('nineteen');
  end; {0-19}

if (a>19)and(a<100) then {20-100}
begin
  case a div 10 of
   2:write('twenty');
   3:write('thirty');
   4:write('forty');
   5:write('fifty');
   6:write('sixty');
   7:write('seventy');
   8:write('eighty');
   9:write('ninety');
  end;
  case a mod 10 of
   1:write('-one');
   2:write('-two');
   3:write('-three');
   4:write('-four');
   5:write('-five');
   6:write('-six');
   7:write('-seven');
   8:write('-eight');
   9:write('-nine');
  end;
end; {20-100}

if (a>99)and(a<1000) then {999-1000}
begin
  if a mod 100=0 then
  begin
  case a div 100 of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
  end;
  write(' hundred');
  end
  else
  begin
  case a div 100 of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
  end;
  write(' hundred and ');
  case (a mod 100)-(a mod 10) of
   20:write('twenty');
   30:write('thirty');
   40:write('forty');
   50:write('fifty');
   60:write('sixty');
   70:write('seventy');
   80:write('eighty');
   90:write('ninety');
  end;
  if a mod 100<20 then
  begin
   case a mod 100 of
    1:write('one');
    2:write('two');
    3:write('three');
    4:write('four');
    5:write('five');
    6:write('six');
    7:write('seven');
    8:write('eight');
    9:write('nine');
    10:write('ten');
    11:write('eleven');
    12:write('twelve');
    13:write('thirteen');
    14:write('fourteen');
    15:write('fifteen');
    16:write('sixteen');
    17:write('seventeen');
    18:write('eighteen');
    19:write('nineteen');
   end;
  end
  else
  begin
   case a mod 10 of
    1:write('-one');
    2:write('-two');
    3:write('-three');
    4:write('-four');
    5:write('-five');
    6:write('-six');
    7:write('-seven');
    8:write('-eight');
    9:write('-nine');
    end;
   end;
  end;
end; {999-1000}
end;

if n>999
then
begin
write(' thousand ');
n:=n-1000*a;

if (n<100) and (n>0)
then
  write('and ');
end;

if (n>0)and(n<20) then {0-19}
  case n of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
   10:write('ten');
   11:write('eleven');
   12:write('twelve');
   13:write('thirteen');
   14:write('fourteen');
   15:write('fifteen');
   16:write('sixteen');
   17:write('seventeen');
   18:write('eighteen');
   19:write('nineteen');
  end; {0-19}

if (n>19)and(n<100) then {20-100}
begin
  case n div 10 of
   2:write('twenty');
   3:write('thirty');
   4:write('forty');
   5:write('fifty');
   6:write('sixty');
   7:write('seventy');
   8:write('eighty');
   9:write('ninety');
  end;
  case n mod 10 of
   1:write('-one');
   2:write('-two');
   3:write('-three');
   4:write('-four');
   5:write('-five');
   6:write('-six');
   7:write('-seven');
   8:write('-eight');
   9:write('-nine');
  end;
end; {20-100}

if (n>99)and(n<1000) then {999-1000}
begin
  if n mod 100=0 then
  begin
  case n div 100 of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
  end;
  write(' hundred');
  end
  else
  begin
  case n div 100 of
   1:write('one');
   2:write('two');
   3:write('three');
   4:write('four');
   5:write('five');
   6:write('six');
   7:write('seven');
   8:write('eight');
   9:write('nine');
  end;
  write(' hundred and ');
  case (n mod 100)-(n mod 10) of
   20:write('twenty');
   30:write('thirty');
   40:write('forty');
   50:write('fifty');
   60:write('sixty');
   70:write('seventy');
   80:write('eighty');
   90:write('ninety');
  end;
  if n mod 100<20 then
  begin
   case n mod 100 of
    1:write('one');
    2:write('two');
    3:write('three');
    4:write('four');
    5:write('five');
    6:write('six');
    7:write('seven');
    8:write('eight');
    9:write('nine');
    10:write('ten');
    11:write('eleven');
    12:write('twelve');
    13:write('thirteen');
    14:write('fourteen');
    15:write('fifteen');
    16:write('sixteen');
    17:write('seventeen');
    18:write('eighteen');
    19:write('nineteen');
   end;
  end
  else
  begin
   case n mod 10 of
    1:write('-one');
    2:write('-two');
    3:write('-three');
    4:write('-four');
    5:write('-five');
    6:write('-six');
    7:write('-seven');
    8:write('-eight');
    9:write('-nine');
    end;
   end;
  end;
end; {999-1000}

writeln;
end.
