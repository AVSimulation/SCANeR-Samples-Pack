import dash
import dash_core_components as dcc
import dash_html_components as html

import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from dash.dependencies import Input, Output
import dash_table
import pandas as pd


def display():
    df = pd.read_csv("results.csv")
    
    lab = {}
    
    for col in df.columns:
        lab[col]=col
        
    
    fig1 = px.parallel_coordinates(df, color="result", labels=lab,color_continuous_scale=[(0.00, "red"),   (0.5, "yellow"),
                                                        (1.0, "blue")])
                                
    # prepare data for pie chart
    df2 = df.value_counts('result').to_frame().reset_index()
    df2.columns = ['results', 'counts']
    df2['results'].replace({0: "Failed", 1: "Success", 0.5: "Warning"}, inplace=True)
    print(df2)
    fig2 = px.pie(df2, values='counts', names='results', title='Test results', color='results', color_discrete_map={'Failed':'red',
                                    'Success':'green',
                                    'Warning':'yellow'})
    
    
    app = dash.Dash()
    app.layout = html.Div([
        dcc.Graph(figure=fig1), dcc.Graph(figure=fig2),
        dash_table.DataTable(
            id='datatable-interactivity',
            columns=[
                {"name": i, "id": i} for i in df.columns
            ],
            data=df.to_dict('records'),
            editable=True,
            filter_action="native",
            sort_action="native",
            sort_mode="multi",
            column_selectable="single",
            page_action="native",
            page_current= 0,
            page_size= 10,
        ),
        html.Div(id='datatable-interactivity-container')
    ])
    
    app.run_server(debug=True, use_reloader=False)