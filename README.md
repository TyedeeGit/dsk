<a id="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![project_license][license-shield]][license-url]

<br />
<div align="center">

<h3 align="center">DTL Standard Kit</h3>

  <p align="center">
    Tools for developing DTL software
    <br />
    <a href="https://github.com/TyedeeGit/dsk"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/TyedeeGit/dsk">View Demo</a>
    ·
    <a href="https://github.com/TyedeeGit/dsk/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/TyedeeGit/dsk/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#about-dtl">About DTL</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

The DSK is the standard collection of tools for developing DTL software.

<!-- ABOUT DTL -->
### About DTL

DTL, or Dependently Typed Language, aims to introduce a static dependent type system to general purpose programming.
Its syntax is inspired by [Python](https://www.python.org/) and type system by [Lean4](https://lean-lang.org/).
Here is an example of a DTL program showcasing a few basic features:  

```dtl
// Import from DTL Standard Library
import dsl.basic
import dsl.io
open DSL

// Inductive parametric data type
inductive MyList(T: Data) -> Data where
    // Nil constructor with implicit argument @T: Data
    constructor nil(@T: Data) -> MyList(T)
    // Cons constructor with implicit arguments @T: Data and explicit arguments t: T and ts: MyList(T)
    constructor cons(@T: Data, t: T, ts: MyList(T)) -> MyList(T)

// Structure type
structure Point where
    field x: Int
    field y: Int

// Enum type
enum Color where
    constructor red: Color
    constructor green: Color
    constructor blue: Color

// Declarations
decl def MyList.map(@A @B: Data, f: A -> B, l: MyList(A)) -> MyList(B)

// Higher order function    
def MyList.map(@A @B: Data, f: A -> B, l: MyList(A)) -> MyList(B) :=
    // Pattern matching
    match l with
        case .nil()       :: nil()
        case .cons(t, ts) :: cons(f(t), MyList.map(f, ts))
        
// Typeclass implementation
implement: Functor(MyList) where
    .map := MyList.map
    
let x: Fin(3) := <2, @> // Pair `2: Nat`, `@: 2 < 3`, @ tells the compiler to infer a proof.
let f: Int -> Int := (@@ + 3) // Partially apply existing functions using @@ notation
let f_alt: Int -> Int := fun(y: Int) -> y + 3 // Equivalent using lambda notation

// Propositions and theorems
theorem succ_add(a b: Nat) -> a++ + b = (a + b)++ by
    // Induction proof using pattern matching
    match b with
        case 0 by
            rw Nat.add_zero(a++), Nat.add_zero(a)
            rfl
        case pb++ by
            rw Nat.add_succ(a++, pb), Nat.add_succ(a, pb++), Nat.succ_add(a, pb)
            rfl

// Main function
def main() -> Unit do
    println("Hello, World!")
    // Python-style f-string
    let name: String := "Gianmarco Lenzi"
    println(f"The creator of DTL is {name}.")
    
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

<!-- TODO: Add usage examples, link to docs -->
_For more examples, please refer to the [Documentation]()_

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] DTL Standard Runtime
- [ ] DTL Standard Compiler
- [ ] DTL Standard Library
    - [ ] Extended DTL Standard Library

See the [open issues](https://github.com/TyedeeGit/dsk/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Top contributors:

<a href="https://github.com/TyedeeGit/dsk/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=TyedeeGit/dsk" alt="contrib.rocks image" />
</a>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

* Gianmarco Lenzi
  * [Github](https://github.com/TyedeeGit)
  * [Email](mailto://tyedee09@gmail.com)


Project Link: [https://github.com/TyedeeGit/dsk](https://github.com/TyedeeGit/dsk)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/TyedeeGit/dsk.svg?style=for-the-badge
[contributors-url]: https://github.com/TyedeeGit/dsk/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/TyedeeGit/dsk.svg?style=for-the-badge
[forks-url]: https://github.com/TyedeeGit/dsk/network/members
[stars-shield]: https://img.shields.io/github/stars/TyedeeGit/dsk.svg?style=for-the-badge
[stars-url]: https://github.com/TyedeeGit/dsk/stargazers
[issues-shield]: https://img.shields.io/github/issues/TyedeeGit/dsk.svg?style=for-the-badge
[issues-url]: https://github.com/TyedeeGit/dsk/issues
[license-shield]: https://img.shields.io/github/license/TyedeeGit/dsk.svg?style=for-the-badge
[license-url]: https://github.com/TyedeeGit/dsk/blob/master/LICENSE.txt
