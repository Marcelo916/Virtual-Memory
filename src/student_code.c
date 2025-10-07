#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"



bool is_entry_valid(PageTableEntry pte) {
  // todo;
  return is_bit_set(pte, VALID_BIT);
}

bool is_read_enabled(PageTableEntry pte) {
  // todo
  // Question: Implement this function.  Hint: it can take as little as 1 line.
  return is_bit_set(pte, READ_BIT);
}

bool is_write_enabled(PageTableEntry pte) {
  // todo
  return is_bit_set(pte, WRITE_BIT);
}

bool is_execute_enabled(PageTableEntry pte) {
  // todo
  return is_bit_set(pte, EXEC_BIT);
}


PFN find_free_page(MMU m) {
  // todo
  for (PFN i = 0; i < NUM_FRAMES; i++) {
      if (!m.page_used[i]) {
          return i;
      }
  }
  return -1; // Indicate no free page found
}

PFN convert_PageTableEntry_to_PFN(PageTableEntry pte) {
  // todo
  AddressMask pfn_mask = get_mask(NUM_PFN_BITS);
  return pte & pfn_mask;
}


/*
 * Page Table Functions
 */
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VPN vpn) {
  // todo
  return m.page_pointer[vpn];
}

PFN map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec) {
  // todo
  PFN free_page = find_free_page(*m);
  if (free_page == (PFN)-1) {
      return free_page;
  }

  PageTableEntry pte = free_page;
  if (can_read) pte |= single_bit_mask(READ_BIT);
  if (can_write) pte |= single_bit_mask(WRITE_BIT);
  if (can_exec) pte |= single_bit_mask(EXEC_BIT);
  pte |= single_bit_mask(VALID_BIT);

  m->page_pointer[vpn] = pte;
  m->page_used[free_page] = true;

  return free_page;
}


/*
 * Page Directory Functions
 */

Page* get_page(MMU m, VirtualAddress va, bool for_read, bool for_write, bool for_execute) {
  // todo
  VPN vpn = va >> NUM_OFFSET_BITS;

  PageTableEntry pte = get_pagetableentry__MMU_pagetable(m, vpn);
  if (!is_entry_valid(pte)) return NULL;
  if (for_read && !is_read_enabled(pte)) return NULL;
  if (for_write && !is_write_enabled(pte)) return NULL;
  if (for_execute && !is_execute_enabled(pte)) return NULL;

  PFN pfn = convert_PageTableEntry_to_PFN(pte);
  return (Page*)&m.physical_memory[pfn * PAGE_SIZE];
}

char read_byte(MMU m, VirtualAddress va) {
  // todo
  Page* page = get_page(m, va, true, false, false);
  if (!page) return '\0';

  OFFSET offset = va & get_mask(NUM_OFFSET_BITS);
  return page->data[offset];
}

void write_byte(MMU m, VirtualAddress va, char val) {
  // todo
  Page* page = get_page(m, va, false, true, false);
  if (!page) return;

  OFFSET offset = va & get_mask(NUM_OFFSET_BITS);
  page->data[offset] = val;
}
