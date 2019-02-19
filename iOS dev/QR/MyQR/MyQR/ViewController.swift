//
//  ViewController.swift
//  MyQR
//
//  Created by Nikolay Fedotenko on 18/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate {
    
    private var Tokens: [String] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        newPasswordLabel.delegate = self
        
        
        //Looks for single or multiple taps.
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(dismissKeyboard))
        
        //Uncomment the line below if you want the tap not not interfere and cancel other interactions.
        //tap.cancelsTouchesInView = false
        
        view.addGestureRecognizer(tap)
    }
    
    
    //Calls this function when the tap is recognized.
    @objc func dismissKeyboard() {
        //Causes the view (or one of its embedded text fields) to resign the first responder status.
        view.endEditing(true)
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return Tokens.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cellPrototype = tableView.dequeueReusableCell(withIdentifier: "tokenCell") else {
            print("cannot dequeueReusableCell withIdentifier tokenCell")
            return TokenTableCell()
        }
        
        guard let cell = cellPrototype as? TokenTableCell else {
            print("cannot cast cellprototype to cell")
            return cellPrototype
        }
        
        cell.Token = Tokens[indexPath.row]
        cell.host = self
        cell.tokenId = indexPath.row
        return cell
    }
    
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var newPasswordLabel: UITextField!
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }
    
    @IBAction func addTokenPressed(_ sender: Any) {
        
        guard var newPassword = newPasswordLabel.text else {
            return // need text
        }
        
        newPassword = newPassword.trimmingCharacters(in: NSCharacterSet.whitespacesAndNewlines)
        
        if newPassword.count == 0 {
            return // need text
        }
        
        if isValidToken(newPassword) {
            return // not unique
        }
        
        Tokens.append(newPassword)
        newPasswordLabel.text = ""
        
        tableView.reloadData()
        
    }
    
    @IBAction func scanQRPressed(_ sender: Any) {
        performSegue(withIdentifier: "scanQRSegue", sender: self)
    }
    
    private var showId: Int = -1
    
    func showQRFor(_ tokenId: Int) {
        showId = tokenId
        performSegue(withIdentifier: "showQRSegue", sender: self)
    }
    
    func removeToken(_ tokenId: Int) {
        Tokens.remove(at: tokenId)
        tableView.reloadData()
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showQRSegue" {
            guard let showController = segue.destination as? ShowQRViewController else {
                print("cast failed")
                return
            }
            showController.setToken(Tokens[showId])
        } else if segue.identifier == "scanQRSegue" {
            guard let scanController = segue.destination as? ScanQRViewController else {
                print("cast failed")
                return
            }
            scanController.host = self
        }
    }
    
    func isValidToken(_ newPassword: String) -> Bool {
        if Tokens.firstIndex(of: newPassword) != nil {
            return true
        }
        return false
    }
}

