#include "MenuBar.hpp"
#include <QMenu>
#include <QMenuBar>
#include <QApplication>



MenuBar::MenuBar(int server_socket, QWidget *parent) : QMainWindow(parent) {

  this->server_socket = server_socket;

  QMenu *productMenu;
  QMenu *propertyMenu;
  QMenu *categoryMenu;
  QMenu *detailMenu;

  productMenu = menuBar()->addMenu(tr("&Products"));

  QAction *insertProp = new QAction("&Insert Property", this);
  QAction *displayProp = new QAction("&Display Property", this);
  QAction *updateProp = new QAction("&Update Property", this);
  QAction *deleteProp = new QAction("&Delete Property", this);

  QAction *insertCategory = new QAction("&Insert Category", this);
  QAction *insertCatToCat = new QAction("&Insert Into Category-To-Category", this);
  QAction *updateCategoryByName = new QAction("&Update Category By Name", this);
  QAction *updateCategoryById = new QAction("&Update Category By Id", this);
  QAction *deleteCategoryById = new QAction("&Delete Category By Id", this);
  QAction *deleteCategoryByName = new QAction("&Delete Category By Name", this);

  QAction *insertDetails = new QAction("&Insert Details", this);
  QAction *viewDetails = new QAction("&View Details", this);

  connect(insertProp, &QAction::triggered, this, &MenuBar::showInsert);
  connect(displayProp, &QAction::triggered, this, &MenuBar::showDisplay);
  connect(updateProp, &QAction::triggered, this, &MenuBar::showUpdate);
  connect(deleteProp, &QAction::triggered, this, &MenuBar::showDelete);

  connect(insertCategory, &QAction::triggered, this, &MenuBar::showInsertCategory);
  connect(insertCatToCat, &QAction::triggered, this, &MenuBar::showInsertCatToCat);
  connect(updateCategoryByName, &QAction::triggered, this, &MenuBar::showUpdateCatByName);
  connect(updateCategoryById, &QAction::triggered, this, &MenuBar::showUpdateCatById);
  connect(deleteCategoryByName, &QAction::triggered, this, &MenuBar::showDeleteCatByName);
  connect(deleteCategoryById, &QAction::triggered, this, &MenuBar::showDeleteCatById);

  connect(insertDetails, &QAction::triggered, this, &MenuBar::showInsertStock);
  connect(viewDetails, &QAction::triggered, this, &MenuBar::showDetails);

  propertyMenu = productMenu->addMenu(tr("&Property"));
  propertyMenu->addAction(insertProp);
  propertyMenu->addAction(displayProp);
  propertyMenu->addAction(updateProp);
  propertyMenu->addAction(deleteProp);

  categoryMenu = productMenu->addMenu(tr("&Category"));
  categoryMenu->addAction(insertCategory);
  categoryMenu->addAction(insertCatToCat);
  categoryMenu->addAction(updateCategoryById);
  categoryMenu->addAction(updateCategoryByName);
  categoryMenu->addAction(deleteCategoryById);
  categoryMenu->addAction(deleteCategoryByName);

  detailMenu = productMenu->addMenu(tr("&Details"));
  detailMenu->addAction(insertDetails);
  detailMenu->addAction(viewDetails);

  QAction *quit = new QAction("&Quit", this);
  quit->setShortcut(tr("CTRL+Q"));

  productMenu->addSeparator();
  productMenu->addAction(quit);

  qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

  connect(quit, &QAction::triggered, qApp, &QApplication::quit);
}
 
MenuBar::~MenuBar() {
  if(insertWindow != nullptr) {
    delete insertWindow;
  } else if(displayWindow != nullptr) {
    delete displayWindow;
  } else if(updateWindow != nullptr) {
    delete updateWindow;
  } else {
    delete deleteWindow;
  }
}

void MenuBar::showInsert(bool checked) {
  insertWindow = new WindowInsert(server_socket);
  insertWindow->show();
}

void MenuBar::showDisplay(bool checked) {
  displayWindow = new WindowDisplay(server_socket);
  displayWindow->show();
}

void MenuBar::showUpdate(bool checked) {
  updateWindow = new WindowUpdate(server_socket);
  updateWindow->show();
}

void MenuBar::showDelete(bool checked) {
  deleteWindow = new WindowDelete(server_socket);
  deleteWindow->show();
}

void MenuBar::showInsertCategory(bool checked) {
  insertCategoryWindow = new WindowInsertCategory(server_socket);
  insertCategoryWindow->show();
}

void MenuBar::showInsertCatToCat(bool checked) {
  insertCatToCatWindow = new WindowInsertCatToCat(server_socket);
  insertCatToCatWindow->show();
}

void MenuBar::showUpdateCatByName(bool checked) {
  renameCatByNameWindow = new WindowRenameCatByName(server_socket);
  renameCatByNameWindow->show();
}

void MenuBar::showUpdateCatById(bool checked) {
  renameCatByIdWindow = new WindowRenameCatById(server_socket);
  renameCatByIdWindow->show();
}

void MenuBar::showDeleteCatByName(bool checked) {
  deleteCatByNameWindow = new WindowDeleteCatByName(server_socket);
  deleteCatByNameWindow->show();
}

void MenuBar::showDeleteCatById(bool checked) {
  deleteCatByIdWindow = new WindowDeleteCatById(server_socket);
  deleteCatByIdWindow->show();
}

void MenuBar::showInsertStock(bool checked) {
  insertStockWindow = new WindowStock(server_socket);
  insertStockWindow->show();
}

void MenuBar::showDetails(bool checked) {
  windowDetails = new WindowDetails(server_socket);
  windowDetails->show();
}

