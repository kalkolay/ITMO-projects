//
//  File.swift
//  
//
//  Created by Samu András on 2020. 02. 19..
//

import SwiftUI

public struct MultiLineChartView: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    var data:[MultiLineChartData]
    public var title: String
    public var legend: String?
    public var style: ChartStyle
    public var darkModeStyle: ChartStyle
    public var formSize: CGSize
    public var dropShadow: Bool
    public var valueSpecifier:String
    
    @State private var hideHorizontalLines: Bool = false
    @State private var touchLocation:CGPoint = .zero
    @State private var showIndicatorDot: Bool = false
    @State private var currentValue: Double = 2 {
        didSet{
            if (oldValue != self.currentValue && showIndicatorDot) {
                HapticFeedback.playSelection()
            }
            
        }
    }
    
    var globalMin:Double {
        if let min = data.flatMap({$0.onlyPoints()}).min() {
            return min
        }
        return 0
    }
    
    var globalMax:Double {
        if let max = data.flatMap({$0.onlyPoints()}).max() {
            return max
        }
        return 0
    }
    
    var frame = CGSize(width: 180, height: 120)
    private var rateValue: Int?
    
    public init(data: [([Double], GradientColor)],
                title: String,
                legend: String? = nil,
                style: ChartStyle = Styles.lineChartStyleOne,
                form: CGSize = ChartForm.extraLarge,
                rateValue: Int? = nil,
                dropShadow: Bool = true,
                valueSpecifier: String = "%.1f") {
        
        self.data = data.map({ MultiLineChartData(points: $0.0, gradient: $0.1)})
        self.title = title
        self.legend = legend
        self.style = style
        self.darkModeStyle = style.darkModeStyle != nil ? style.darkModeStyle! : Styles.lineViewDarkMode
        self.formSize = form
        frame = CGSize(width: self.formSize.width, height: self.formSize.height/2)
        self.rateValue = rateValue
        self.dropShadow = dropShadow
        self.valueSpecifier = valueSpecifier
    }
    
    public var body: some View {
        ZStack(alignment: .center){
            RoundedRectangle(cornerRadius: 20)
                .fill(self.colorScheme == .dark ? self.darkModeStyle.backgroundColor : self.style.backgroundColor)
                .frame(width: frame.width, height: 240, alignment: .center)
                .shadow(radius: self.dropShadow ? 8 : 0)
            VStack(alignment: .leading) {
                if(!self.showIndicatorDot){
                    VStack(alignment: .leading, spacing: 8){
                        Text(self.title)
                            .font(.title)
                            .bold()
                            .foregroundColor(self.colorScheme == .dark ? self.darkModeStyle.textColor : self.style.textColor)
                        if (self.legend != nil){
                            Text(self.legend!)
                                .font(.callout)
                                .foregroundColor(self.colorScheme == .dark ? self.darkModeStyle.legendTextColor : self.style.legendTextColor)
                        }
//                        HStack {
//                            if (rateValue ?? 0 >= 0){
//                                Image(systemName: "arrow.up")
//                            }else{
//                                Image(systemName: "arrow.down")
//                            }
//                            Text("\(rateValue ?? 0)%")
//                        }
                    }
//                    .transition(.opacity)
//                    .animation(.easeIn(duration: 0.1))
                    .padding([.leading, .top])
                }else{
//                    HStack{
//                        Spacer()
//                        Text("\(self.currentValue, specifier: self.valueSpecifier)")
//                            .font(.system(size: 41, weight: .bold, design: .default))
//                            .offset(x: 0, y: 30)
//                        Spacer()
//                    }
//                    .transition(.scale)
                }
                Spacer()
                GeometryReader{ geometry in
                    ZStack{
                        Legend(data: ChartData(points: data.map { $0.onlyPoints() }.reduce([], +)),
                               frame: .constant(geometry.frame(in: .local)),
                               hideHorizontalLines: $hideHorizontalLines)
                        
                        ForEach(0..<self.data.count) { i in
                            Line(data: self.data[i],
                                 frame: .constant(geometry.frame(in: .local).insetBy(dx: 18, dy: -13.2)),
                                 touchLocation: self.$touchLocation,
                                 showIndicator: self.$showIndicatorDot,
                                 minDataValue: .constant(self.globalMin),
                                 maxDataValue: .constant(self.globalMax),
                                 showBackground: false,
                                 gradient: self.data[i].getGradient(),
                                 index: i)
                                .padding(.leading, 36)
                                .padding(.bottom, 0.5)
                        }
                    }
                }
                .padding()
                .frame(width: frame.width, height: frame.height + 50)
                .clipShape(RoundedRectangle(cornerRadius: 20))
//                .offset(x: 0, y: 0)
            }.frame(width: self.formSize.width, height: self.formSize.height)
        }
        .gesture(DragGesture()
                    .onChanged({ value in
                        //            self.touchLocation = value.location
                        //            self.showIndicatorDot = true
                        //            self.getClosestDataPoint(toPoint: value.location, width:self.frame.width, height: self.frame.height)
                    })
                    .onEnded({ value in
                        self.showIndicatorDot = false
                    })
        )
    }
    
    //    @discardableResult func getClosestDataPoint(toPoint: CGPoint, width:CGFloat, height: CGFloat) -> CGPoint {
    //        let points = self.data.onlyPoints()
    //        let stepWidth: CGFloat = width / CGFloat(points.count-1)
    //        let stepHeight: CGFloat = height / CGFloat(points.max()! + points.min()!)
    //
    //        let index:Int = Int(round((toPoint.x)/stepWidth))
    //        if (index >= 0 && index < points.count){
    //            self.currentValue = points[index]
    //            return CGPoint(x: CGFloat(index)*stepWidth, y: CGFloat(points[index])*stepHeight)
    //        }
    //        return .zero
    //    }
}

struct MultiWidgetView_Previews: PreviewProvider {
    static var previews: some View {
        Chart(function: function)
    }
    
    static let function: (_ x: Double, _ a: Double, _ U: Double) -> Double = { x, a, U in
        return abs(x) < a ? -U : 0
    }
    
    static func Chart(function: ((_ x: Double, _ a: Double, _ U: Double) -> Double)) -> some View {
        let leftBorder: Double = -10
        let rightBorder: Double = 10
        var points = [Double]()
        
        for x in stride(from: leftBorder, to: rightBorder, by: 0.1) {
            points.append(function(Double(x), 3, 2))
        }
        
        return MultiLineChartView(data: [(points, GradientColor(start: .red, end: .red))],
                                  title: "Потенциальная яма",
                                  form: ChartForm.extraLarge)
    }
}
