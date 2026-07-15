#  Minishell Tester

An automated, highly comparative integration test suite for the 42 School **minishell** project. 

The script cross-references your custom shell's output, directory file generation, exit codes, and error logging directly against system **Bash** execution.

---

##  Test Categories & Modules

The tester organizes evaluation files systematically. You can run all modules or selectively pick targets:

*   `syntax`: Quoting states, parsing anomalies, empty commands, and semi-colons.
*   `extras`: Edge cases, relative paths, absolute binaries, and special parameters.
*   `builtins`: Custom environment actions (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).
*   `pipes`: Complex pipeline sequences, structural fork boundaries, and execution blocking.
*   `redir_in`: Standard redirection controls (`<`).
*   `redir_out`: Output redirection controls (`>`).
*   `redir_append`: Append-redirection validation (`>>`).
*   `redir_mix`: Interactive mixed redirections (`cat < infile > outfile >> appendfile`).

<div align="center">
    <br>
    <a href="https://github.com/tdanielsousa/42_School/blob/main/Subjects/minishell_subject.pdf" target="_blank">
        <img src="https://img.shields.io/badge/View%20Subject-PDF-red?style=for-the-badge&logo=adobe-acrobat-reader&logoColor=white" alt="Subject PDF" height="40">
    </a>
    <p><i>Click on the button above to see the subject's pdf.</i></p>

</div>

---

##  Core Validation Protocol

To guarantee precise checks, the script handles several background operations:

### 1. Dynamic Prompt Sanitization
Minishell projects often print styled interactive prompts.  
The tester identifies your prompt dynamically, strips raw ANSI color codes using `sed`, and filters it out of the output logs so it only evaluates true commands:

    PROMPT=$(echo -e "\nexit\n" \vert{} $MINISHELL_PATH | head -n 1 | sed "s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g" )

### 2. Output and Directory Isolation
If a test creates, modifies, or appends files (e.g. inside a test folder `./outfiles/`), the script mirrors these transactions into separate comparison directories: `./mini_outfiles/` and `./bash_outfiles/`.  
It then performs a `diff` across generated documents to catch unexpected writing errors.

### 3. Exit Code Checking
Since your minishell runs inside a subshell structure during testing, the script uses a customized pipe routing method to securely extract the precise `$?` exit code from your processes:

    MINI_EXIT_CODE=$(echo -e "$MINISHELL_PATH\n$teste\necho \$?\nexit\n" | bash ...)

### 4. Detailed Visual Diagnostics
If a validation check fails, the console displays color-coded logs pinpointing differences across four distinct points:
*   **Outputs:** Standard output string conflicts.
*   **Exit Codes:** Mismatched process values (e.g., Minishell returned `1` but Bash returned `127`).
*   **Generated Files:** Dynamic differences detected inside custom files.
*   **Stderr Warnings (⚠️):** The tester flags output matches that have divergent error messages.

---

##  Installation & Usage

### 1. Setup
Clone this repository directly alongside your `minishell` directory (the default setting assumes your `minishell` executable is located at `../minishell` relative to the tester script).

    git clone [https://github.com/tdanielsousa/minishell_tester.git](https://github.com/tdanielsousa/minishell_tester.git)
    cd minishell_tester

### 2. Run All Test Suites
Ensure your minishell binary is compiled, then run the test script:

    ./test.sh

### 3. Run a Specific Test Module
You can target a single test file by passing its name as an argument:

    ./test.sh builtins

*Or for redirections:*

    ./test.sh redir_mix

---

