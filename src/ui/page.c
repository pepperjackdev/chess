#include "ui/page.h"

#include "ui/game_page.h"

void update_page(Page page) {
  switch (page.page_type) {
    case GAME:
      update_game_page(page.page_data);
      break;
  }
}

void render_page(Page page) {
  switch (page.page_type) {
    case GAME:
      render_game_page((GamePage*)page.page_data);
      break;
  }
}

