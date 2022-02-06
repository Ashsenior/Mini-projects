'''
    Functions inside the header file to use >>>

    ready_data() function for cleaning and filling data from start to end
    ready_data(csv_file_name,num_method="median",time_series=False)

    get_time_series() function to get time series dataframe and convert it into numerical form
    get_time_series(csv_file)

    scale() scale function scales your data and returns dataframe with all scaled columns
    scale(df)

    remove_least_correlated_columns() function removes all least correlated columns with the label with a factor
    remove_least_correlated_columns(df,label,factor=3)

'''
import pandas as pd 
import numpy as np
from sklearn.preprocessing import StandardScaler

def ready_data(csv_file_name,num_method="median",time_series=False):
    df = pd.read_csv(csv_file_name+".csv",low_memory=False)
    if time_series:
        datec = get_date_column(csv_file_name)
        df = pd.read_csv(csv_file_name+".csv",low_memory=False,parse_date=[datec])
        df.sort_values(by=[datec],inplace=True,ascending=True)
    for label ,content in df.items():
        if pd.api.types.is_string_dtype(content):
            df[label] = content.astype("category").cat.as_ordered()
    for label,content in df.items():
        if pd.api.types.is_categorical_dtype(content):
            df[label] = pd.Categorical(content).codes+1
        if pd.api.types.is_datetime64_dtype(content):
            df[label] = content.dropna(axis=0,inplace=True)
        elif pd.api.types.is_numeric_dtype(content):
            if pd.isnull(content).sum():
                df[label+'_is_missing'] = pd.isnull(content)
                if num_method=='median':
                    df[label] = content.fillna(content.median())
                else :
                    df[label] = content.fillna(content.mean())
    if time_series:
        df.Year = df[datec].dt.year
        df.Month = df[datec].dt.month
        df.day = df[datec].dt.day
        df.DayOfWeek = df[datec].dt.dayofweek
        df.DayOfYear = df[datec].dt.dayofyear
        df.drop(datec,axis=1,inplace=True)
    scaled_df = scale(df)
    print("NOTE : New columns were added in your dataframe including (is_missing) columns and (date) columms. ")
    return scaled_df

def get_time_series(csv_file):
    datec = get_date_column(csv_file)
    df = pd.read_csv(csv_file_name+".csv",low_memory=False,parse_date=[datec])
    df.sort_values(by=[datec],inplace=True,ascending=True)
    for label,content in df.items():
        if pd.api.type.is_datetime64_dtype(content):
            df[label] = content.dropna(axis=0,inplace=True)
    df.Year = df[datec].dt.year
    df.Month = df[datec].dt.month
    df.day = df[datec].dt.day
    df.DayOfWeek = df[datec].dt.dayofweek
    df.DayOfYear = df[datec].dt.dayofyear
    df.drop(datec,axis=1,inplace=True)
    print("NOTE : New columns were added in your dataframe .")
    return df

def scale(df):
    scaler = StandardScaler()
    scaled_df = pd.DataFrame(scaler.fit_transform(df),columns=df.columns)
    return scaled_df

def remove_least_correlated_columns(df,label,factor=3):
    least_corr = []
    count=0
    neg_limit = df.corr()[label][df.corr()[label]<0].mean()/factor
    pos_limit = df.corr()[label][df.corr()[label]>0].mean()/factor
    for i in range(len(df.corr()[label])):
        val=df.corr()[label][i]
        if neg_limit<val<pos_limit:
            least_corr.append(df.corr().index[i])
            print(f" Column **{df.corr().index[i]}** was removed with correlation {val} with {label}")
            count+=1;
    if count==0:
        print(" No column was removed from DataFrame")
    df = df.drop(least_corr,axis=1)
    return df