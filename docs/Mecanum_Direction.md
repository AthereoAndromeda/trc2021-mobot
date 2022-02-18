# Mecanum Wheel Direction
Changing directions for the Mecanum wheels is achieved with the `setMotorDir()` function.
If you were to look at it's body, it would look rather confusing at first. It assigns a weird-looking number-letter combination to `PORTA` and
somehow that changes the direction of the mobot.

So let's discuss what exactly is happening here. First off, what's this number and letter thingy?

### Hexadecimal and Binary
These letter and number combinations are actually just another way to represent numbers. Hexadecimal. This system operates on base-16, meaning there are 16
symbols. These symbols are `0-9`, and `A-F` for the extra 6 characters. Or in full `0123456789ABCDEF`.

This is just a numbering system, just like binary, and decimal. They are just different ways of representing the same thing. Numbers.

Humans use the Decimal system, which is base-10, meaning there are 10 symbols used. These symbols are `0123456789`.  
Computers on the other hand uses Binary, which is a base-2 system. There are only 2 values, `0` and `1`.

In C++, we prefix binary numbers with `0b` to indicate they are binary. We do the same with hexadecimal using `0x`
For example, if we wanted to write the binary number `10100010` and the hexadecimal number `A2`, we'd do it as such:
```cpp
// These 3 variables are equal, despite looking very different
// Notice that all three variables use the `int` data type
int binNum = 0b10100010;
int hexNum = 0xA2;
int decimalNum = 162;

if ((binNum == hexNum) && (binNum == decimalNum) && (hexNum == decimalNum)) {
  Serial.println("These numbers are the same!"); // This Runs!
}
```

Thing is, computers can **ONLY** understand Binary. They can't understand Decimal, and yes, even Hexadecimal. Whenever we use a
*non-binary* system or number, the CPU automatically converts it into Binary. Otherwise it the CPU can't understand it. So why
do we bother with using Hexadecimal if it still has to be converted just like Decimal?

Because Hexadecimal very easily maps to Binary, and it is much shorter (like Faye) compared to an equivalent Binary number.
The CPU has an easier time converting Hexadecimal compared to Decimal. This is because Hexadecimal is a base-16 system. 16 is a multiple of 2 (specifically
2^4). This means 1 digit of Hexadecmial can be represented with 4 digits of Binary. Hexadecimal can also be considered a more human-readable and condensed form 
of Binary. You can use 2 digits of hex to represent a byte (8 bits), for example: `11100111` as `E7` in Hex.

So why do we care about Hexadecimal and Binary? Because we can use them for Port Manipulation which is ***much*** faster than `digitalWrite()`.
~64ns compared to ~5us. ***Massively faster***. The CPU is 16Mhz which means it cycles every 62.5ns. It literally only limited by how fast the CPU cycles.
We don't have to use Port Manipulation, and just use `digitalWrite()` instead, but for this project we decided to do utilize them.

### Port Manipulation
Okay, how exactly do we use Port Manipulation then? Make sure to watch the FB Live from TRC for a more detailed explanation.

Take a look at this diagram:
![Arduino Mega 2560 Pinouts](https://content.instructables.com/ORIG/F2R/VII9/JESSUPJM/F2RVII9JESSUPJM.png?auto=webp&fit=bounds&frame=1&width=1024)

In this Mobot, all the pins related to Mecanum Wheel Direction are conveniently placed on `PORTA`. There are 8 pins on `PORTA`, the exact size of 1 byte, or 8 bits. 

We can use a Binary number to switch pins on like this.
```cpp
PORTA = 0b00000000; // Set Pins 0-7 to LOW
```
Notice there are 8 numbers after the `0b`. Each of those numbers is a `bit` that correlates to a certain pin in `PORTA`.
How do we know which bit correlates to which pin? Quite simple actually, the rightmost bit is Pin 0, and the leftmost bit is Pin 7.
(Relative to the diagram, or `PORTA`. As in Pin 7 of `PORTA`, but not Pin 7 of the entire Arduino. Pin 7 of `PORTA` is equal to Pin 29 of Arduino)

```cpp
PORTA = 0b10000001; // Pin 0 and Pin 7 are HIGH. The rest are LOW

PORTA = 0b00000110; // Pin 1 and Pin 2 are HIGH. The rest are LOW

PORTA = 0b11111101; // Pin 2 is LOW. The rest are HIGH
```
So that's how we can use binary for port manipulation. At this point I would recommend you watch the Port Manipulation FB Live to know
AND OR NOT bitwise operations and more stuff.

Now, how does this affect the direction of the mobot? The pins are setup in a way such that 2 bits correlate to a specific wheel.  
It might be more understandable in code
```cpp
// It might be easier to understand if we space out the bits to represent each wheel
// 0b01100010 becomes 0b 01 10 00 10
// Note: Spacing the bits isn't valid C++ code, it's just used to better visualize and understand.

// This is the specific wheel each set of bit represents.
//
// 0b 00 00 00 00
//    TR TL BL BR
//
//    or
// Top_Right Top_Left Bottom_Left Bottom_Right

// Depending on the pair of bits, it determines which direction the rotor of the individual wheel will rotate
// 00 and 11 -> Do Nothing
// 10 -> Rotate Clockwise
// 01 -> Rotate CounterClockwise

// So lets check out how it works in code 

PORTA = 0b 00 00 00 00; // Does nothing to All rotors

PORTA = 0b 10 00 00 01; // Top_Right rotates clockwise, Bottom_Right rotates CounterClockwise

PORTA = 0b 10 10 10 10; // Rotates all rotors clockwise           (This causes Mobot to move Forward)

PORTA = 0b 01 01 01 01; // Rotates all rotors counterclockwise    (Causes mobot to move Backward)

PORTA = 0b 10 01 01 10; // Top_Right and Bottom_Right rotate clockwise, Top_Left and Bottom_Left rotate counterclockwise (Causes mobot to move counterclockwise)

// Remember that spacing out the bits isn't valid, it's just there to help visualize it easier.
// To convert to valid C++, all you have to do is remove the spacing betwen the bits.

// These are valid now
PORTA = 0b10101010; // Rotates all rotors clockwise
PORTA = 0b01010101; // Rotates all rotors counterclockwise
PORTA = 0b10010110; // Top_Right and Bottom_Right rotate clockwise, Top_Left and Bottom_Left rotate counterclockwise
```

The above code would work normally. So the next question is why hexadecimal then?  
Well it's quite simple. It's just shorter to write than binary. Seriously, that's it.

With hexadecimal, you can represent 1 byte, or 8 bits, with only 2 characters. To convert between hexadecimal and binary,
just use some online calculator. Wait, didn't you say it was easy to convert from hexadecimal to binary and vice-versa?

Yes. Easy for computers which operate on base-2. Not so much for us humans who are used to a base-10 system. Also the Arduino runs at like
16 Megahertz, which is 16 million cycles per second. 

The code should be equivalent to the code above
```cpp
PORTA = 0x00; // Does nothing to All rotors

PORTA = 0x81; // Top_Right rotates clockwise, Bottom_Right rotates CounterClockwise

PORTA = 0xAA; // Rotates all rotors clockwise           (This causes Mobot to move Forward)

PORTA = 0x55; // Rotates all rotors counterclockwise    (Causes mobot to move Backward)

PORTA = 0x96; // Top_Right and Bottom_Right rotate clockwise, Top_Left and Bottom_Left rotate counterclockwise (Causes mobot to move counterclockwise)
```
As you can see, it's much shorter than Binary. only 2 digits.

Of course, it's still hard to remember which set of bits corresponds to which Direction or movement. Humans are much more adept at recognizing
strings, or names rather than a meaningless collection of numbers.

### Enum
This is where Enums help! Enums (short for Enumeration) are a date type that contains integral constants. You can think of these
as a sort of "multiple choice" data type.
```cpp
enum MotorDirection {
  Forward,
  Backward,
  Left,
  Right,
  Stop
};
```

By default, these choices are actually just integers but with a name so we can more easily remember them and know their purporse.
For example, `Forward` is actually just 0, `Backward` is 1, and so on. We can change the default value, but we won't talk about it here.

This means you can also do this
```cpp
MotorDirection direction = Forward;

if (direction == Forward) {
  // Preferred method
}

if (direction == 0) {
  // This also works!
}
```

So anyways that's a short overview of Enum. Now how we map directions with Enums

### Setting Directions with Enum
A switch case is used to match an enum, and that sets the direction

```cpp
void setMotorDir(Direction dir) {
  switch (dir) {
    case Forward:
      PORTA = 0xAA;
      break;
    
    case Backward:
      PORTA = 0x55;
      break;
      
    case Left:
      PORTA = 0x99;
      break;

    case Right:
      PORTA = 0x66;
      break;
      
    case Stop:
      PORTA = 0xFF;
      break;
  }
}
```

There are many more directions than this obviously, but this is the general gist of how we change direction. With the use of Enums, we can use
easy-to-remember keywords like `Forward`, `Backward`, `Left`, etc. Whereas with direct port manipulation, we have to use numbers and unfamiliar digits
that aren't immediately obvious what direction it's going without a comment.

That's all for now folks, see ya

## Footnotes
While writing this, i realized `setMotorDir` might be redunant. It might be possible to just stick the values
directly to the enum as such:
```cpp
enum MotorDirection {
  Forward = 0xAA,
  Backward = 0x55,
  Left = 0x99,
  Right = 0x66,
  Stop = 0xFF
};
```

Then within `runMotors()`, we could directly assign it to `PORTA` without calling a function.
```cpp
void motorMove(Direction direction, uint16_t duration) {
  // setMotorDir(direction);
  PORTA = direction;
  runMotors();

  delay(duration);
  stopMotors();
}
```

It would remove a redundant function, and maybe a slight performance boost since there is 1 less function to call.  
Dunno still haven tested it yet
