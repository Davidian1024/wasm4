import MultiLanguageCode from '@site/src/components/MultiLanguageCode';

# User Input

## Gamepad

The main input device is the gamepad, consisting of 4 directions and 2 action
buttons. On computers, players use the arrow keys and the X and Z keys. On
mobile, a virtual gamepad overlay is displayed that players can tap.

The gamepad state is stored by WASM-4 as one byte in memory, with each button
stored as a single bit. For example, the right directional button is stored in
bit 5. We can mask the gamepad with the `BUTTON_RIGHT` constant to check if the
right button is pressed.

<MultiLanguageCode>

```typescript
const gamepad = load<u8>(w4.GAMEPAD1);

if (gamepad & w4.BUTTON_RIGHT) {
    w4.trace("Right button is down!");
}
```

```c
unsigned char gamepad = *GAMEPAD1;

if (gamepad & BUTTON_RIGHT) {
    trace("Right button is down!");
}
```

```rust
let gamepad = unsafe { *GAMEPAD1 };

if gamepad & BUTTON_RIGHT != 0 {
    trace("Right button is down!");
}
```

```go
var gamepad = *GAMEPAD1;

if (gamepad & BUTTON_RIGHT != 0) {
    trace("Right button is down!");
}
```

</MultiLanguageCode>

| Gamepad Bit | Button                |
| ---         | ---                   |
| 0           | `BUTTON_1` (1)        |
| 1           | `BUTTON_2` (2)        |
| 2           | *Unused*              |
| 3           | *Unused*              |
| 4           | `BUTTON_LEFT` (16)    |
| 5           | `BUTTON_RIGHT` (32)   |
| 6           | `BUTTON_UP` (64)      |
| 7           | `BUTTON_DOWN` (128) |

### Checking if a button was pressed this frame

`GAMEPAD1` stores the current state of the gamepad. It's common to want to know
if a button was just pressed this frame. Another way of putting it: if a
button was *not* down last frame but *is* down this frame.

This can be handled by storing the previous gamepad state, and then [bitwise
XORing](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Bitwise_XOR) (`^`)
it with the current gamepad state. This leaves us with a byte with only the
buttons that were pressed this frame.

<MultiLanguageCode>

```typescript
let previousGamepad: u8;

export function update () {
    const gamepad = load<u8>(w4.GAMEPAD1);

    // Only the buttons that were pressed down this frame
    const pressedThisFrame = gamepad & (gamepad ^ previousGamepad);
    previousGamepad = gamepad;

    if (pressedThisFrame & w4.BUTTON_RIGHT) {
        trace("Right button was just pressed!");
    }
}
```

```c
unsigned char previousGamepad;

void update () {
    unsigned char gamepad = *GAMEPAD1;

    // Only the buttons that were pressed down this frame
    unsigned char pressedThisFrame = gamepad & (gamepad ^ previousGamepad);
    previousGamepad = gamepad;

    if (pressedThisFrame & BUTTON_RIGHT) {
        trace("Right button was just pressed!");
    }
}
```

```rust
// Rust example coming soon 🦀
```

```go
var previousGamepad byte;

//go:export update
func update () {
    var gamepad = *GAMEPAD1;

    // Only the buttons that were pressed down this frame
    var pressedThisFrame = gamepad & (gamepad ^ previousGamepad);
    previousGamepad = gamepad;

    if (pressedThisFrame & BUTTON_RIGHT != 0) {
        trace("Right button was just pressed!");
    }
}
```

</MultiLanguageCode>

## Mouse

Mouse (or touchscreen) input is supported. See the [Memory Map](/docs/reference/memory)
reference for more details on `MOUSE_X`, `MOUSE_Y`, and `MOUSE_BUTTONS`.