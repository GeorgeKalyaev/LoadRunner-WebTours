CSStopExecution=false;
CSAct = new Object;
var myChart;

$(document).ready(function () {
	var data = $('#csv').html();
	var title = '';
	var xAxisTitle = $('#xAxisTitle').html();
	var yAxisTitle = $('#yAxisTitle').html();
	var yRightAxisTitle = $('#yRightAxisTitle').html();
	var type = $('#Type').html();
	var notTimeBased = false;

	if ($('#timeBasedLinearGraph').html() == 'false')
		notTimeBased = true;
	
	if (type == 'line')
	{
		myChart = new Highcharts.Chart('graphContainer', {
	        chart: {
	            type: 'line',
	            description: $('#myDescr').html()
	        },
	        title: {
	            text: title
	        },
			credits: { 
				enabled: false 
			},
	    	plotOptions:{
	    		series:{
	    			connectNulls: true
	    		},
	    	},
	    	xAxis: {
	    		title:{
	    			text: xAxisTitle 
	    		},
				type:'datetime',
				labels:{
					formatter: function() {
						return getTimeFormat(this.value);
					}
				}
	    	},
	    	yAxis: [
				{
	    		title:{
	    			text: yAxisTitle 
				}
				}, 
				{
				title:{
					text: yRightAxisTitle
				},
				opposite:true
			}],
			tooltip: {
				formatter: function() {
					return getTimeFormat(this.x);
				}
			}
    	});
	}
	else if (type == 'column')
	{
		myChart = new Highcharts.Chart('graphContainer', {
	        chart: {
	            type: 'column'
	        },
	        title: {
	            text: title
	        },
			credits: { 
				enabled: false 
			},
	    	plotOptions:{
	    		series: {
         		   minPointLength: 3
        		}    		
	    	},
	    	yAxis: {
	    		title:{
	    			text: yAxisTitle 
	    		}
	    	}
	    	
    	});
	}
	else if (type == 'pie')
	{
		myChart = new Highcharts.Chart('graphContainer', {
	        chart: {
	            type: 'pie'
	        },
	        title: {
	            text: title
	        }, 
			series:[{
				data:[]
			}],
			credits: { 
				enabled: false 
			},
	    	plotOptions:{
	    		pie:{
	    			dataLabels: {
                    	enabled: false
                	},
	    			showInLegend: true
	    		}
	    	},
			tooltip:{
				pointFormat:'<b>{point.y}</b>'
			}
    	});
	}
	else if (type == 'area')
	{
		myChart = new Highcharts.Chart('graphContainer', {
	        chart: {
	            type: 'area'
	        },
	        title: {
	            text: title
	        },
			credits: { 
				enabled: false 
			},
	    	plotOptions:{
	    		series:{
	    			connectNulls: true
	    		},
	    	},
	    	xAxis: {
	    		title:{
	    			text: xAxisTitle 
	    		},
				type:'datetime',
				labels:{
					formatter: function() {
						return getTimeFormat(this.value);
					}
				}
	    	},
	    	yAxis: [
				{
	    		title:{
	    			text: yAxisTitle 
				}
				}, 
				{
				title:{
					text: yRightAxisTitle
				},
				opposite:true
			}],
			tooltip: {
				formatter: function() {
					return getTimeFormat(this.x);
				}
			}
    	});
	}
	else if (type == 'no-points')
	{
		myChart = new Highcharts.Chart('graphContainer', {
	        chart: {
	            type: 'line'
	        },
	        title: {
	            text: title
	        },
			credits: { 
				enabled: false 
			},
	    	plotOptions:{
	    		series:{
	    			connectNulls: true
	    		},
	    		line:{
	    			marker: {
	    				enabled: false
	    			}
	    		}
	    	},
	    	xAxis: {
	    		title:{
	    			text: xAxisTitle 
	    		},
				type:'datetime',
				labels:{
					formatter: function() {
						return getTimeFormat(this.value);
					}
				}
	    	},
	    	yAxis: [
				{
	    		title:{
	    			text: yAxisTitle 
				}
				}, 
				{
				title:{
					text: yRightAxisTitle
				},
				opposite:true
			}],
			tooltip: {
				formatter: function() {
					return getTimeFormat(this.x);
				}
			}
    	});
	}
	getSeriesData(type, notTimeBased);
});

function getSeriesData(type, notTimeBased){
	myChart.showLoading();
	var sLen = parseInt($("#SeriesCount").text());
	var timestampMultiplier = 1000;

	if(notTimeBased){
		myChart.xAxis[0].update({
			type: 'linear',
			labels: {
				formatter: undefined
			},
		});
		timestampMultiplier = 1;
	}
	for (i = 0; i < sLen; i++) {
		var table = document.getElementById("Values_"+i);
		var axis = $("#Values_"+i).attr('axis'); 
		var data = [];
		var columnCategories = [];

		for (var j = 0; j < table.rows.length; j++) {
		   var cells = table.rows[j].cells;
		   if(cells.length == 3)
				myChart.series[0].addPoint({
					name: cells[0].innerHTML,
					y: parseFloat(cells[1].innerHTML.replace(',', '.')),
					color: cells[2].innerHTML
				})
			else if(cells.length == 2 && type == 'column'){
				columnCategories.push(cells[0].innerHTML); 	
				data.push(parseFloat(cells[1].innerHTML.replace(',', '.'))); 
			}
			else if(cells.length == 2) 
				data.push([parseFloat(cells[0].innerHTML.replace(',', '.'))*timestampMultiplier,parseFloat(cells[1].innerHTML.replace(',', '.'))]);
			else 
				data.push(parseFloat(cells[0].innerHTML.replace(',', '.')));
		}
		if(type == 'column'){
			myChart.xAxis[0].setCategories(columnCategories);
		}
		if(!(type == 'pie'))
			myChart.addSeries({
				name: $("#Values_"+i).attr('title'),
				data: data,
				color: $("#color_"+i).css('backgroundColor'),
				step: $("#Values_"+i).attr('stairs')=="true"
				},false);
		if(axis == 1){
			myChart.series[i].update({
				yAxis: 1
			});
		}
	}
	myChart.redraw();
	myChart.hideLoading();
}

function getTimeFormat(value){
	var xAxisTitle = $('#xAxisTitle').html();
	value = value / 1000;
	var hString = "";
	var mString = "";
	var sString = "";
	
	var hours = Math.floor(value / 3600);
	if (hours < 10)
		hString = "0" + hours;
	else
		hString = hours;

	var remaining = value - hours * 3600;
	var minutes = Math.floor(remaining / 60);
	if (minutes < 10)
		mString = "0" + minutes;
	else
		mString = minutes;

	var remaining = remaining - minutes * 60;
	if(remaining < 10)
		sString = "0" + remaining;
	else
		sString = remaining;

	if(xAxisTitle.indexOf("hh:mm:ss") != -1){
		return hString + ':' + mString + ':' + sString;
	}
	else if(xAxisTitle.indexOf("hh:mm") != -1){
		return hString + ':' + mString;
	}
	else{
		return mString + ':' + sString;
	}
}