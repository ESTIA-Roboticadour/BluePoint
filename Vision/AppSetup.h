#pragma once

#include <QString>
#include <QWidget>

class AppSetup
{
public:
    /// Prépare l’application.  Renvoie true si tout est OK.
    static bool setupApp();

    /// Affiche toutes les infos et warnings emmagasinées pendant setup.
    static void shareMessages();

    /// Affiche la boîte de dialogue d’erreur (s’il y a eu échec).
    static void showError(QWidget* parent = nullptr);

    // Interdire construction / copie
    AppSetup() = delete;
    AppSetup(const AppSetup&) = delete;
    AppSetup& operator=(const AppSetup&) = delete;
};
