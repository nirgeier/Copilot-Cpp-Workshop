# Sample inputs

- `valid.json`: eight ordinary values in the 0 to 1 range.
- `boundary.json`: alternating zeros and ones, the minimum and maximum of the
  expected input range.
- `invalid.json`: contains `1e309`, which becomes a non-finite float. The model
  must reject it with a clear error. Use this case to check that Copilot does
  not add a silent fallback that hides invalid input.

The reader accepts a JSON style object with a `values` array of numbers. It is
deliberately small and is not a general JSON parser.
