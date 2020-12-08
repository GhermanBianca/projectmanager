#pragma once
#include "WindowInsert.hpp"
#include "WindowDisplay.hpp"
#include "WindowUpdate.hpp"
#include "WindowDelete.hpp"
#include "WindowInsertCategory.hpp"
#include "WindowInsertCatToCat.hpp"
#include "WindowRenameCatByName.hpp"
#include "WindowRenameCatById.hpp"
#include "WindowDeleteCatByName.hpp"
#include "WindowDeleteCatById.hpp"
#include "WindowStock.hpp"
#include "WindowDetails.hpp"
#include "StockSimulation.hpp"

#include <QMainWindow>
#include <QApplication>
#include <QDialog>
#include <QTableView>

class MenuBar : public QMainWindow {
    
  public:
  MenuBar(int server_socket, QWidget *parent = 0);
  ~MenuBar();
  WindowInsert *insertWindow {nullptr};
  WindowDisplay *displayWindow {nullptr};
  WindowUpdate *updateWindow {nullptr};
  WindowDelete *deleteWindow {nullptr};
  WindowInsertCategory * insertCategoryWindow {nullptr};
  WindowInsertCatToCat * insertCatToCatWindow {nullptr};
  WindowRenameCatByName *renameCatByNameWindow {nullptr};
  WindowRenameCatById *renameCatByIdWindow {nullptr};
  WindowDeleteCatByName *deleteCatByNameWindow {nullptr};
  WindowDeleteCatById *deleteCatByIdWindow {nullptr};
  WindowStock *insertStockWindow {nullptr};
  WindowDetails *windowDetails {nullptr};
  StockSimulation *stockSimulation {nullptr};

  int server_socket;
  QTableView tableView;

  public slots:
    void showInsert(bool checked);
    void showDisplay(bool checked);
    void showUpdate(bool checked);
    void showDelete(bool checked);
    void showInsertCategory(bool checked);
    void showInsertCatToCat(bool checked);
    void showUpdateCatByName(bool checked);
    void showUpdateCatById(bool checked);
    void showDeleteCatByName(bool checked);
    void showDeleteCatById(bool checked);
    void showInsertStock(bool checked);
    void showDetails(bool checked);
    void showSimulation(bool checked);
};