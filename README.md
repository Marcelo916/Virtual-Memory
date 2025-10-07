# Virtual Memory (Page Tables & MMU in C)

This assignment implements a simplified **memory management unit (MMU)**.  
I map virtual pages to physical frames, enforce **read/write/execute** permissions via page-table bits, and translate virtual addresses to physical memory (PFN + offset). Unit tests cover frame allocation, permission checks, and byte-level reads/writes.

## What I Implemented
- Page-table helpers: `is_entry_valid`, `is_read_enabled`, `is_write_enabled`, `is_execute_enabled`
- Frame management: `find_free_page`, `convert_PageTableEntry_to_PFN`
- Mapping & lookup: `get_pagetableentry__MMU_pagetable`, `map_page__MMU_pagetable`
- Address translation & access: `get_page` (enforces VALID/R/W/X), `read_byte`, `write_byte`

## Build & Run
> Requires **gcc** and **make** (Linux/macOS or Windows via WSL/MSYS2).

```bash
make                 # build (outputs in ./bin)
make test            # run tests (if target exists)
./bin/unit_tests     # or ./bin/debug, depending on starter code
~~~

## NOTES
- The page table stores VALID/R/W/X bits with the PFN; get_page validates permissions before reads/writes.
- On Windows line-ending warnings (“LF will be replaced by CRLF”): add a .gitattributes to keep source and Makefile as LF.
