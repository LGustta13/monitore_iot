chave = "ae4def1ecaae8be24edf7f6453e37f7200ef2e41048da1b17d68978322097cd6"
data = 'https://darwin-gps.com.br/api/abastecimentos/setAbastecimentosInterno.php?chave='+chave + \
    '&abastecimentos=[{"tank_id":1108,"tank_name":"BOMBA TRANSPRINT CAJAMAR","initial_volume":1,"final_volume":2,"drain_value":955.30,"utc_initial_date_time":[{"date":"2000-01-02 11:00:52","timezone_type":3,"timezone":"UTC"}],"utc_final_date_time":[{"date":"2000-01-02 11:00:52","timezone_type":3,"timezone":"UTC"}],"ident_pessoa_apoio":1020744,"ident_veiculo":3308985,"ident_motorista":11247945}]'
data = data.replace('"', '\\"').replace(" ", "%20")
print(data)
