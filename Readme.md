Pretty much follows the posix implementation.
Few mac relics like D ..

# Follows the format:
```text
	%<flag><min_field_width>.<precision><length_modifier><conversion_specifier>
```

# Flags:
```text
	#: alternate form
	-: pad on the right (left-aligned)
	+: shows sign at all times
```

# Length modifier:
```
  hh: char
  h: short
  l: long
  ll: long long
```

# Conversion specifier:
```text
  d,i: prints decimal
  u: prints unsigned decimal
  o: prints octal
  x: prints hexadecimal
  b: prints binary
  s: prints narrow string
  c: prints narrow char
  p: prints pointer (%#lx)
  
  DI: same as ld/li
  O: same as lo
  U: same as lu
  S: prints wide string
  C: prints wide char
```
