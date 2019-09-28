list_of_files <- list.files(path = "./", recursive = TRUE, patter = "\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = 10
colo_for_100 = ""
for (val in list_of_files){
  result = paste("./", val, sep = "")
  if(i != 1) leg = c(leg, paste("N = ", paste0(inici),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  if(i != 1) colo = c(colo, colors()[value])
  else colo_for_100 = colors()[value]
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 2, lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Transmission Radius R")
  lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
  if(i != 1)inici = inici + 10
}

leg = c(leg,"N = 100");
colo = c(colo,colo_for_100)

legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)
