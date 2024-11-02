void buystock(Trader &t1)
{
    int stockChoice;
    cout << "Choose the stock you want to view for purchase:\n";
    cout << "1) AAPL   2) GOOGL   3) MSFT   4) AMZN   5) META\n";
    cout << "6) TSLA   7) NFLX    8) NVDA   9) DIS    10) JPM\n";
    cout << "Enter the number of the stock: ";
    cin >> stockChoice;
    string symbols[MAX_STOCKS] = {"AAPL", "GOOGL", "MSFT", "AMZN", "META", "TSLA", "NFLX", "NVDA", "DIS", "JPM"};
    switch(stockChoice)
    {
        case 1:
        {
           if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
                break;
        }
        case 2:
        {
           if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 3:
        {
            if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 4:
        {
            if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 5:
        {
            if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 6:
        { 
            if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 7:
        {
           if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 8:
        {
           if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 9:
        {
           if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 10:
        {
            if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                show(STOCKS, selectedSymbol); // Call the function from linkedlist.cpp
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                int quantity;
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
                if(STOCKS->qtyAvailable<quantity)
                {
                    cout<<"Quantity exceeded. Chooose between 0 to "<<STOCKS->qtyAvailable<<":"<<endl;
                    buystock(t1);
                }
                else{
                    int total=quantity*(STOCKS->price);    
                    cout<<"Your total purchase for"<<selectedSymbol<<"is"<<total;
                    if(t1.balance>total){
                        //t1.assets(selectedSymbol,STOCKS->price,STOCKS->qtyAvailable);
                    }
                    else{
                        cout<<"Insufficient Balance."<<endl;
                    }
                   }
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
    }
}




{
    {
        void addStockToAssets(const string& symbol, int price, int quantity) {
        if (balance < price * quantity) {
            cout << "Insufficient balance to buy stock." << endl;
            return;
        }
        balance -= price * quantity;
        if (assets.find(symbol) != assets.end()) {
            assets[symbol].second += quantity; // Increase quantity if stock already exists
        } else {
            assets[symbol] = make_pair(price, quantity); // Add new stock to assets
        }

        cout << "Stock " << symbol << " added to portfolio with quantity: " << quantity << " at price: " << price << endl;
        cout << "Remaining balance: " << balance << endl;
    }

    void viewPortfolio() const {
        cout << "Portfolio for " << name << " (ID: " << id << "):" << endl;
        for (const auto& asset : assets) {
            cout << "Stock Symbol: " << asset.first << ", Price: " << asset.second.first
                 << ", Quantity: " << asset.second.second << endl;
        }
    }
    friend void processStockPurchase(Trader &t1, int stockChoice, const string &selectedSymbol, Node *STOCKS);
    map<string,int,int>assets;


    }
}