# protoproj

## Third-party software

This project vendors [Catch2](https://github.com/catchorg/Catch2) v3.16.0
(commit `317ac1ed4c0bb6e6b91eafc817e05c488feffcb3`) in the [`Catch2/`](Catch2)
directory, and builds it as part of the `tests` target that drives the unit
tests in [`test/`](test). Catch2 is only used by the tests and is not linked
into the `main` executable.

Catch2 is licensed under the [Boost Software License
1.0](https://www.boost.org/LICENSE_1_0.txt) (BSL-1.0); the full license text as
shipped by the project is kept at [`Catch2/LICENSE.txt`](Catch2/LICENSE.txt).
