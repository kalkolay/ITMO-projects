//
//  ShowQRViewController.swift
//  MyQR
//
//  Created by Nikolay Fedotenko on 18/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class ShowQRViewController: UIViewController {
    @IBOutlet weak var qrCode: UIImageView!
    private var qrImage: UIImage? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        if let qrImage = qrImage {
            qrCode.image = qrImage
        }
    }
    
    public func setToken(_ password: String) {
        
        // 1
        let myString = password
        // 2
        let data = myString.data(using: String.Encoding.ascii)
        
        // 3
        guard let qrFilter = CIFilter(name: "CIQRCodeGenerator") else { return }
        
        // 4
        qrFilter.setValue(data, forKey: "inputMessage")
        
        // 5
        guard let qrImage = qrFilter.outputImage else { return }
        
        // Get a CIContext
        let context = CIContext()
        
//        // Create the filter
//        guard let maskToAlphaFilter = CIFilter(name: "CIMaskToAlpha") else { return }
//
//        // Create the filter
//
//        guard let colorInvertFilter = CIFilter(name: "CIColorInvert") else { return }

        let transform = CGAffineTransform(scaleX: 10, y: 10)
        let scaledQrImage = qrImage.transformed(by: transform)
//
//        // Set the input image to what we generated above
//
//        colorInvertFilter.setValue(scaledQrImage, forKey: "inputImage")
//
//        // Get the output CIImage
//
//        guard let outputInvertedImage = colorInvertFilter.outputImage else { return }
//
//        // Set the input image to the colorInvertFilter output
//        maskToAlphaFilter.setValue(outputInvertedImage, forKey: "inputImage")
//
//        // Get the output CIImage
//        guard let outputCIImage = maskToAlphaFilter.outputImage else { return }
        
        // Create a CGImage *from the extent of the outputCIImage*
        guard let cgImage = context.createCGImage(scaledQrImage, from: scaledQrImage.extent) else { return }
        
        // Finally, get a usable UIImage from the CGImage
        self.qrImage = UIImage(cgImage: cgImage)
    }
}
