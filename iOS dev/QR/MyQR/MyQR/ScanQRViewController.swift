//
//  ScanQRViewController.swift
//  MyQR
//
//  Created by Nikolay Fedotenko on 18/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit
import AVFoundation

class ScanQRViewController: UIViewController, AVCaptureMetadataOutputObjectsDelegate {
    
    @IBAction func didTapOnTakePhotoButton(_ sender: Any) {
    }
    
    @IBOutlet weak var previewView: UIImageView!
    
    var session: AVCaptureSession?
    var stillImageOutput: AVCaptureStillImageOutput?
    var videoPreviewLayer: AVCaptureVideoPreviewLayer?
    
    public var host: ViewController? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.session = AVCaptureSession()
        guard let session = session else { return }
        
        session.sessionPreset = AVCaptureSession.Preset.photo
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        guard let session = session else { return }
        
        guard let backCamera =  AVCaptureDevice.default(for: AVMediaType.video) else {
            print("no backCamera")
            
            
            let alert = UIAlertController(title: "Error", message: "Sorry, app was unable to reach camera on your device", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
                switch action.style{
                case .default:
                    print("default")
                    
                case .cancel:
                    print("cancel")
                    
                case .destructive:
                    print("destructive")
                    
                }}))
            
            self.present(alert, animated: true, completion: nil)
            
            self.session = nil
            if let nvc = self.navigationController {
                nvc.popViewController(animated: true)
            }
            
            return
        }
        
        var error: NSError?
        var input: AVCaptureDeviceInput!
        do {
            input = try AVCaptureDeviceInput(device: backCamera)
        } catch let error1 as NSError {
            error = error1
            input = nil
            print(error!.localizedDescription)
            
            let alert = UIAlertController(title: "Error", message: "Sorry, problem with AVCaptureDeviceInput()", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
                switch action.style{
                case .default:
                    print("default")
                    
                case .cancel:
                    print("cancel")
                    
                case .destructive:
                    print("destructive")
                    
                }}))
            
            self.present(alert, animated: true, completion: nil)
            
            self.session = nil
            if let nvc = self.navigationController {
                nvc.popViewController(animated: true)
            }
            
            return
        }
        
        if error == nil && session.canAddInput(input) {
            session.addInput(input)
            
            let stillImageOutput = AVCaptureStillImageOutput()
            self.stillImageOutput = stillImageOutput
            
            stillImageOutput.outputSettings = [AVVideoCodecKey:  AVVideoCodecType.jpeg]
            
            if session.canAddOutput(stillImageOutput) {
                session.addOutput(stillImageOutput)
                videoPreviewLayer = AVCaptureVideoPreviewLayer(session: session)
                videoPreviewLayer!.videoGravity =    AVLayerVideoGravity.resizeAspect
                videoPreviewLayer!.connection?.videoOrientation =   AVCaptureVideoOrientation.portrait
                previewView.layer.addSublayer(videoPreviewLayer!)
                session.startRunning()
            } else {
                print("session.canAddOutput(stillImageOutput) failed!")
            }
            
            // Initialize a AVCaptureMetadataOutput object and set it as the output device to the capture session.
            let captureMetadataOutput = AVCaptureMetadataOutput()
            
            if !session.canAddOutput(captureMetadataOutput) {
                
                let alert = UIAlertController(title: "Error", message: "Sorry, problem using AVCaptureMetadataOutput()", preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
                    switch action.style{
                    case .default:
                        print("default")
                        
                    case .cancel:
                        print("cancel")
                        
                    case .destructive:
                        print("destructive")
                        
                    }}))
                
                self.present(alert, animated: true, completion: nil)
                if let nvc = self.navigationController {
                    nvc.popViewController(animated: true)
                }
                
                self.session = nil
                return
                
            }
            
            session.addOutput(captureMetadataOutput)
            
            // Set delegate and use the default dispatch queue to execute the call back
            captureMetadataOutput.setMetadataObjectsDelegate(self, queue: DispatchQueue.main)
            captureMetadataOutput.metadataObjectTypes = [AVMetadataObject.ObjectType.qr]
            
            
        }
        
        guard let videoPreviewLayer = videoPreviewLayer else { return }
        videoPreviewLayer.frame = previewView.bounds
        
        //        // Initialize the video preview layer and add it as a sublayer to the viewPreview view's layer.
        //        videoPreviewLayer = AVCaptureVideoPreviewLayer(session: captureSession)
        //        videoPreviewLayer?.videoGravity = AVLayerVideoGravity.resizeAspectFill
        //        videoPreviewLayer?.frame = view.layer.bounds
        //        view.layer.addSublayer(videoPreviewLayer!)
        
        session.startRunning()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        if let session = session {
            session.stopRunning()
            self.session = nil
        }
    }
    
    func metadataOutput(_ output: AVCaptureMetadataOutput, didOutput metadataObjects: [AVMetadataObject], from connection: AVCaptureConnection) {
        // Check if the metadataObjects array is not nil and it contains at least one object.
        if metadataObjects.count == 0 {
            print("No QR code is detected")
            return
        }
        
        // Get the metadata object.
        let metadataObj = metadataObjects[0] as! AVMetadataMachineReadableCodeObject
        
        if metadataObj.type == AVMetadataObject.ObjectType.qr {
//            // If the found metadata is equal to the QR code metadata then update the status label's text and set the bounds
//            let barCodeObject = videoPreviewLayer?.transformedMetadataObject(for: metadataObj)
//            previewView?.frame = barCodeObject!.bounds
            
            if let qrToken = metadataObj.stringValue {
                print(qrToken)
                
                if let host = host {
                    if host.isValidToken(qrToken) {
                        self.view.backgroundColor = UIColor.green
                    } else {
                        self.view.backgroundColor = UIColor.red
                    }
                }
                
            } else {
                print("metadata empty string value")
            }
        }
    }
    
}
